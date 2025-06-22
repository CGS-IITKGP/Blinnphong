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
#include "stb_image.h"

// =================== ImGui ===================
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

// Window dimensions
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Camera instance (extern in processInput and mouse)
Camera camera(glm::vec3(0.0f, 1.0f, 12.0f));

// Light variables
glm::vec3 lightPos(2.0f, 4.0f, 2.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
float shininess = 32.0f;

// Point lights positions
glm::vec3 pointLightPositions[] = {
    glm::vec3(2.0f, 4.0f, 2.0f),
    glm::vec3(-2.0f, 4.0f, 2.0f),
    glm::vec3(2.0f, 4.0f, -2.0f),
    glm::vec3(-2.0f, 4.0f, -2.0f)
};

// ImGui variables
bool showImGuiWindow = true;
const char* scenes[] = { "Castle", "Other" };
int scene_type = 0;

// Callback for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int createWhiteTexture()
{
    unsigned int tex;
    unsigned char whitePixel[3] = { 255, 255, 255 };
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, whitePixel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
}
int main()
{
    // GLFW init
    cout << " 1.start " << endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    cout << " 2. Window " << endl;
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
    cout << " glad " << endl;
    glEnable(GL_DEPTH_TEST);

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    cout << " imgui " << endl;
    // Load your shaders
    Shader lightingShader("vertex_shader.glsl", "fragment_shader.glsl");
    lightingShader.use();
    lightingShader.setInt("diffuseMap", 0);
    lightingShader.setInt("specularMap", 1);
    cout << " shader " << endl;
    float lightIntensity = 1.0f;

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image with stb_image
    int width, height, nrChannels;
    unsigned char* data = stbi_load("C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\wall.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    //cout << " T1 " << endl;
    unsigned int carTextures[3];
    //cout << " bla " << endl;
    const char* texturePaths[] = {
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\moon.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\untitled.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\wheel.jpg"
    };
    cout << " T2.1.2.3. " << endl;
    glGenTextures(3, carTextures);
    //cout << " glgen " << endl;
    for (int i = 0; i < 3; ++i) {
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(texturePaths[i], &width, &height, &nrChannels, 0);
        //cout << " done*+  " << endl;
        glBindTexture(GL_TEXTURE_2D, carTextures[i]);

        if (!data) {
            std::cerr << " Failed to load texture: " << texturePaths[i] << std::endl;

            // Use 1x1 white fallback pixel
            unsigned char whitePixel[] = { 255, 255, 255 };
            //cout << " bla " << endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, whitePixel);
            //cout << " bla " << endl;
            continue;
        }
        else {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            //cout << " hello " << endl;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            //cout << " deb " << endl;
            glGenerateMipmap(GL_TEXTURE_2D);
            //cout << " ug " << endl;
            stbi_image_free(data);
            cout << " Loaded texture: " << texturePaths[i] << std::endl;
        }

        // Set texture parameters (even for fallback)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    // Load model (castle.fbx)
    Model castleModel("C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\utubecastle.fbx");
    Model carModel("C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\cartutorial.fbx");
    cout << "Loading model: " << "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\utubtecastle.fbx" << std::endl;
    int currentModelIndex = 0;
    // Model transform controls for ImGui
    glm::vec3 modelPosition(0.0f);
    glm::vec3 modelRotation(0.0f);
    float modelScale = 1.0f;
    glm::vec3 modelAxis(0.0f, 1.0f, 0.0f); // Rotation axis (Y axis by default)
    
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Toggle ImGui window with F5
        static bool f5WasPressed = false;
        if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS) {
            if (!f5WasPressed) {
                showImGuiWindow = !showImGuiWindow;
                f5WasPressed = true;
            }
        }
        else {
            f5WasPressed = false;
        }

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui window
        if (showImGuiWindow) {
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            float windowWidth = display_w * 0.2f;
            float windowHeight = display_h * 0.3f;
            // Set position to bottom-right
            ImVec2 windowPos = ImVec2(10,10);
            ImVec2 windowSize = ImVec2(windowWidth, windowHeight);
            ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
            ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
            ImGui::Begin("Scene Controls", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImGui::Text("Use keyboard: Tab/Arrows/Enter");
            ImGui::SliderFloat3("Light Position", glm::value_ptr(lightPos), -10.0f, 10.0f);
            ImGui::SliderFloat("Shininess", &shininess, 1.0f, 256.0f);
            //ImGui::ColorEdit3("Light Color", glm::value_ptr(lightColor));
            ImGui::SliderFloat("Color Intensity", &lightIntensity, 0.0f, 10.0f);
            const char* modelNames[] = { "Castle", "Car" };
            ImGui::Combo("Model", &currentModelIndex, modelNames, IM_ARRAYSIZE(modelNames));
            ImGui::End();
        }

        // Clear screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        lightingShader.use();
        //lightingShader.setVec3("lightColor", lightColor); // Modulated intensity
        lightingShader.setFloat("lightIntensity", lightIntensity *0.1f); // Modulated intensity
        lightingShader.setFloat("shininess", shininess);

        // Set lighting uniforms
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.ambient", 0.01f, 0.01f, 0.01f);
        lightingShader.setVec3("dirLight.diffuse", 0.1f, 0.1f, 0.1f);
        lightingShader.setVec3("dirLight.specular", 0.1f, 0.1f, 0.1f);

        for (int i = 0; i < 4; i++) {
            std::string prefix = "pointLights[" + std::to_string(i) + "].";
            lightingShader.setVec3(prefix + "position", pointLightPositions[i]);
            lightingShader.setVec3(prefix + "ambient", 0.05f, 0.05f, 0.05f);
            lightingShader.setVec3(prefix + "diffuse", 0.8f, 0.8f, 0.8f);
            lightingShader.setVec3(prefix + "specular", 1.0f, 1.0f, 1.0f);
            lightingShader.setFloat(prefix + "constant", 1.0f);
            lightingShader.setFloat(prefix + "linear", 0.09f);
            lightingShader.setFloat(prefix + "quadratic", 0.032f);
        }

        lightingShader.setVec3("spotLight.position", camera.Position);
        lightingShader.setVec3("spotLight.direction", camera.Front);
        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.09f);
        lightingShader.setFloat("spotLight.quadratic", 0.032f);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        lightingShader.setVec3("light.position", lightPos);
        lightingShader.setVec3("lightColor", lightColor);
        lightingShader.setFloat("material.shininess", shininess);

        // View/projection matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        lightingShader.setVec3("viewPos", camera.Position);

        // Or, use the modelAxis for custom axis rotation:
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, modelPosition);
        model = glm::scale(model, glm::vec3(modelScale));
        if (currentModelIndex == 0) {
            // Castle specific rotation
            model = glm::rotate(model, glm::radians(modelRotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(modelRotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(modelRotation.z), glm::vec3(0, 0, 1));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        else if (currentModelIndex == 1) {
            // Car specific rotation if needed
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        lightingShader.setMat4("model", model);
        
        // Draw model
        if (currentModelIndex == 0) {
            for (auto& mesh : castleModel.meshes) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureID);
                mesh.textures.clear();  // clear old
                Texture tex;
                tex.id = textureID;
                tex.type = "texture_diffuse"; // or "material.diffuse1"
                tex.path = "wall.jpg";
                mesh.textures.push_back(tex);
            }
            castleModel.Draw(lightingShader);
        }
        else if (currentModelIndex == 1) {
            //glActiveTexture(GL_TEXTURE0);  // Set active texture unit before binding
            //glBindTexture(GL_TEXTURE_2D, textureID);  // Optional: bind a fallback/base texture
            //for (int i = 0; i < carModel.meshes.size(); ++i) {
            //    carModel.meshes[i].textures.clear();

            //    Texture tex;
            //    tex.id = carTextures[i % 3]; // Cycle through 3 car-specific textures
            //    tex.type = "texture_diffuse";  // Must match the shader's uniform type
            //    tex.path = texturePaths[i % 3];

            //    carModel.meshes[i].textures.push_back(tex);
            //}

            //carModel.Draw(lightingShader);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, carTextures[0]); // Use first car texture

            // Bind white texture to specular slot (since we don't have specular map)
            static unsigned int whiteTex = createWhiteTexture();
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, whiteTex);

            carModel.Draw(lightingShader);
        }
        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
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
