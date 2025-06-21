// =================== Standard Includes ===================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// =================== OpenGL / GLFW ===================
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

// =================== GLM ===================
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// =================== Project Headers ===================
#include "shader.h"
#include "camera.h"
#include "mouse.h"
#include "processInput.h"
#include "model.h"

// =================== ImGui ===================
// IMPORTANT: Define loader before OpenGL3 header
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

// Window dimensions
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Camera instance (extern in processInput and mouse)
Camera camera(glm::vec3(0.0f, 5.0f, 15.0f));

// Callback for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // GLFW init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Castle Model with ImGui", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Capture mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLAD load
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Load your shaders
    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

    // Load model (castle.fbx) - make sure castle.fbx and wall.jpg are in working directory
    Model castleModel("C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\cartutorial.fbx");
    std::cout << "Loading model: " << "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\cartutorial.fbx" << std::endl;
    // Model transform controls for ImGui
    glm::vec3 modelPosition(0.0f);
    glm::vec3 modelRotation(0.0f);
    float modelScale = 1.0f;

    // Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
        (float)SCR_WIDTH / (float)SCR_HEIGHT,
        0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input handling
        processInput(window);

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui window for model controls
        ImGui::Begin("Model Controls");
        ImGui::SliderFloat3("Position", glm::value_ptr(modelPosition), -10.0f, 10.0f);
        ImGui::SliderFloat3("Rotation (degrees)", glm::value_ptr(modelRotation), -180.0f, 180.0f);
        ImGui::SliderFloat("Scale", &modelScale, 0.1f, 5.0f);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();

        // Clear screen
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        shader.use();

        // Update projection and view matrices
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);
        shader.setMat4("view", camera.GetViewMatrix());

        // Model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, modelPosition);
        model = glm::rotate(model, glm::radians(modelRotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(modelRotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(modelRotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(modelScale));
        shader.setMat4("model", model);

        // Draw the model
        castleModel.Draw(shader);

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    fs::path file_path = "C:/Users/JASMINE/Desktop/Blinnphong/assets/castle.fbx";
    try {
        auto perms = fs::status(file_path).permissions();
        if ((perms & fs::perms::owner_read) != fs::perms::none) {
            std::cout << "You have read permission." << std::endl;
        }
        else {
            std::cout << "You do NOT have read permission." << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    // Cleanup ImGui and GLFW
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
