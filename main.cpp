#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"
#include "mouse.h"
#include "processInput.h"
#include "model.h"
#include "stb_image.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

// Window
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
float clear_color[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Camera
Camera camera(glm::vec3(0.0f, 1.0f, 12.0f));

// Light!!!
glm::vec3 pointLightPositions[] = {
    glm::vec3(2.0f, 4.0f, 2.0f),
    glm::vec3(-2.0f, 4.0f, 2.0f),
    glm::vec3(2.0f, 4.0f, -2.0f),
    glm::vec3(-2.0f, 4.0f, -2.0f)
};
glm::vec3 lightPos = pointLightPositions[0];
//glm::vec3 lightPos(2.0f, 4.0f, 2.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
// Directional Light Defaults 
glm::vec3 defaultDirLightDir = glm::vec3(-0.2f, -1.0f, -0.3f);
glm::vec3 defaultDirLightAmbient = glm::vec3(0.01f);
glm::vec3 defaultDirLightDiffuse = glm::vec3(0.1f);
glm::vec3 defaultDirLightSpecular = glm::vec3(0.1f);

// Point Light Default
glm::vec3 defaultPointLightPos = pointLightPositions[0];  // initial position
glm::vec3 defaultPointAmbient = glm::vec3(0.05f);
glm::vec3 defaultPointDiffuse = glm::vec3(0.8f);
glm::vec3 defaultPointSpecular = glm::vec3(1.0f);
float defaultPointConst = 1.0f, defaultPointLinear = 0.09f, defaultPointQuad = 0.032f;

// Spot Light Defaults
glm::vec3 defaultSpotAmbient = glm::vec3(0.0f);
glm::vec3 defaultSpotDiffuse = glm::vec3(1.0f);
glm::vec3 defaultSpotSpecular = glm::vec3(1.0f);
float defaultSpotConst = 1.0f, defaultSpotLinear = 0.09f, defaultSpotQuad = 0.032f;
float defaultSpotCutoff = glm::cos(glm::radians(12.5f));
float defaultSpotOuterCutoff = glm::cos(glm::radians(15.0f));

// === Runtime Editable Copies ===
glm::vec3 dirLightDir = defaultDirLightDir;
glm::vec3 dirLightAmbient = defaultDirLightAmbient;
glm::vec3 dirLightDiffuse = defaultDirLightDiffuse;
glm::vec3 dirLightSpecular = defaultDirLightSpecular;

glm::vec3 pointLightPos = defaultPointLightPos;
glm::vec3 pointLightAmbient = defaultPointAmbient;
glm::vec3 pointLightDiffuse = defaultPointDiffuse;
glm::vec3 pointLightSpecular = defaultPointSpecular;
float pointConst = defaultPointConst, pointLinear = defaultPointLinear, pointQuad = defaultPointQuad;

glm::vec3 spotLightAmbient = defaultSpotAmbient;
glm::vec3 spotLightDiffuse = defaultSpotDiffuse;
glm::vec3 spotLightSpecular = defaultSpotSpecular;
float spotConst = defaultSpotConst, spotLinear = defaultSpotLinear, spotQuad = defaultSpotQuad;
float spotCutoff = defaultSpotCutoff, spotOuterCutoff = defaultSpotOuterCutoff;

float shininess = 32.0f;
float lightIntensity = 2.0f;

bool useDirLight = true;
bool usePointLights = true;
bool useSpotLight = true;

// ImGui
bool showImGuiWindow = true;
const char* scenes[] = { "Castle", "Other" };
int scene_type = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int createWhiteTexture()
{
    unsigned int tex;
    unsigned char whitePixel[3] = { 255, 255, 255 };
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
}
int main()
{
    // GLFW init
    std::cout << " 1.start " << endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    cout << " 2. Window " << endl;
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dual with ImGui setup", NULL, NULL);
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
    // shaders
    Shader lightingShader("vertex_shader.glsl", "fragment_shader.glsl");
    lightingShader.use();
    lightingShader.setInt("diffuseMap", 0);
    lightingShader.setInt("specularMap", 1);
    cout << " shader " << endl;
    float lightIntensity = 1.0f;

    vector<string> texturePaths2 = {
    "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\wall.jpg",
    "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\Diffuse_Bake_4k.jpg",
    "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\alexander-andrews-vGCErDhrc3E-unsplash.jpg"
    "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\moon.jpg"
    };

    vector<unsigned int> textureIDs(texturePaths2.size());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int width, height, nrChannels;

    // Generate texture IDs
    glGenTextures(texturePaths2.size(), textureIDs.data());

    for (size_t i = 0; i < texturePaths2.size(); ++i) {
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        unsigned char* data = stbi_load(texturePaths2[i].c_str(), &width, &height, &nrChannels, 4);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            std::cout << "Loaded texture: " << texturePaths2[i] << std::endl;
        }
        else {
            std::cerr << "Failed to load texture: " << texturePaths2[i] << std::endl;
        }
        stbi_image_free(data);
    }

    unsigned int sceneTextures[18];
    const char* texturePaths[] = {
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\2048_steel_stain_diffuse.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\BricksLongThinRunningExtruded001_COL_2K_METALNESS.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Classic Window v4_BaseColor.1001.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Classical Window v3_BaseColor.1001.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Classical Window7_BaseColor.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Dirtyemptypot_color.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\download.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\concrete_wall_diffuse.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\door2_15_BaseColor.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Lamp_2_BaseColor.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Mansion Door_BaseColor.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Material_BaseColor.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\height_Out.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Image_2.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\Mossy Ground_height.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\Mossy Ground_normal.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\Mossy Ground_roughness.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\StuccoIndoor_GLOSS_1K.tif",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\Mud_height.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\Mud_normal.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\Mud_roughness.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene\\Normals_Out.jpg",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\StuccoIndoor_NRM_1K.tif",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\TexturesCom_Stucco1_1024_normal.tif",
        //"C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\TexturesCom_Stucco1_1024_roughness.tif",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\deadleaves.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Autumn leaves.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Previrew_var1.jpg",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\tree_bark_19_color.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\Screenshot 2025-05-17 234126.png",
        "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\vecteezy_a-group-of-trees-in-the-middle-of-a-field_51765352.png",
    };
    glGenTextures(18, sceneTextures);
    for (int i = 0; i < 18; ++i) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(texturePaths[i], &width, &height, &nrChannels, 4);
        glBindTexture(GL_TEXTURE_2D, sceneTextures[i]);

        if (!data) {
            std::cerr << " Failed to load texture: " << texturePaths[i] << std::endl;

            // Use 1x1 white fallback pixel
            unsigned char whitePixel[] = { 255, 255, 255 };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);
            continue;
        }
        else {
            cout << "1 ";
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            cout << "pew";
            glGenerateMipmap(GL_TEXTURE_2D);
            cout << "pew";
            stbi_image_free(data);
        }

        // Setting texture parameters (even for fallback)
        cout << "pew";
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        cout << "pew";
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        cout << "pew";
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        cout << "pew";
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    cout << "pew";
    // Loading  model
    Model castleModel("C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\utubecastle.fbx");
    cout << "pew";

    Model sceneModel("C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\Scene2\\House_topengl.fbx");
    cout << "pew";

    if (castleModel.meshes.empty()) std::cerr << "castleModel failed to load!" << std::endl;
    if (sceneModel.meshes.empty()) std::cerr << "sceneModel failed to load!" << std::endl;
    cout << "Loading model: " << "C:\\Users\\JASMINE\\Desktop\\Blinnphong\\assets\\utubtecastle.fbx" << std::endl;
    int currentModelIndex = 0;
    if (sceneModel.meshes.empty()) {
        std::cerr << "sceneModel has no meshes loaded!" << std::endl;
    }
    // Model transform controls for ImGui
    glm::vec3 modelPosition(0.0f);
    glm::vec3 modelRotation(0.0f);
    float modelScale = 1.0f;
    glm::vec3 modelAxis(0.0f, 1.0f, 0.0f);

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
            float windowWidth = display_w * 0.3f;
            float windowHeight = display_h * 0.32f;
            // Set position to bottom-right
            ImVec2 windowPos = ImVec2(10, 10);
            ImVec2 windowSize = ImVec2(windowWidth, windowHeight);
            ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
            ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
            ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImGui::Text("Use keyboard: Tab/Arrows/Enter");
            ImGui::ColorEdit3("Window Color", clear_color);
            //ImGui::Begin("Lighting Editor");

            if (ImGui::Button("Reset to Default")) {
                // dEFAULT VALUES
                dirLightDir = defaultDirLightDir;
                dirLightAmbient = defaultDirLightAmbient;
                dirLightDiffuse = defaultDirLightDiffuse;
                dirLightSpecular = defaultDirLightSpecular;

                pointLightPos = defaultPointLightPos;
                pointLightAmbient = defaultPointAmbient;
                pointLightDiffuse = defaultPointDiffuse;
                pointLightSpecular = defaultPointSpecular;
                pointConst = defaultPointConst;
                pointLinear = defaultPointLinear;
                pointQuad = defaultPointQuad;

                spotLightAmbient = defaultSpotAmbient;
                spotLightDiffuse = defaultSpotDiffuse;
                spotLightSpecular = defaultSpotSpecular;
                spotConst = defaultSpotConst;
                spotLinear = defaultSpotLinear;
                spotQuad = defaultSpotQuad;
                spotCutoff = defaultSpotCutoff;
                spotOuterCutoff = defaultSpotOuterCutoff;

                shininess = 32.0f;
                lightIntensity = 2.0f;
                useDirLight = true;
                usePointLights = true;
                useSpotLight = true;
            }

            // === Directional Light ===
            if (ImGui::CollapsingHeader("Directional Light")) {
                ImGui::Checkbox("Enable Directional Light", &useDirLight);
                ImGui::SliderFloat3("Direction", glm::value_ptr(dirLightDir), -1.0f, 1.0f);
                ImGui::ColorEdit3("Ambient", glm::value_ptr(dirLightAmbient));
                ImGui::ColorEdit3("Diffuse", glm::value_ptr(dirLightDiffuse));
                ImGui::ColorEdit3("Specular", glm::value_ptr(dirLightSpecular));
            }

            // === Point Light ===
            if (ImGui::CollapsingHeader("Point Light")) {
                ImGui::Checkbox("Enable Point Light", &usePointLights);
                ImGui::SliderFloat3("Position", glm::value_ptr(pointLightPos), -10.0f, 10.0f);
                ImGui::ColorEdit3("Ambient", glm::value_ptr(pointLightAmbient));
                ImGui::ColorEdit3("Diffuse", glm::value_ptr(pointLightDiffuse));
                ImGui::ColorEdit3("Specular", glm::value_ptr(pointLightSpecular));
                ImGui::SliderFloat("Constant", &pointConst, 0.0f, 2.0f);
                ImGui::SliderFloat("Linear", &pointLinear, 0.0f, 1.0f);
                ImGui::SliderFloat("Quadratic", &pointQuad, 0.0f, 1.0f);
            }

            // === Spot Light ===
            if (ImGui::CollapsingHeader("Spot Light")) {
                ImGui::Checkbox("Enable Spot Light", &useSpotLight);
                ImGui::ColorEdit3("Ambient", glm::value_ptr(spotLightAmbient));
                ImGui::ColorEdit3("Diffuse", glm::value_ptr(spotLightDiffuse));
                ImGui::ColorEdit3("Specular", glm::value_ptr(spotLightSpecular));
                ImGui::SliderFloat("Constant", &spotConst, 0.0f, 2.0f);
                ImGui::SliderFloat("Linear", &spotLinear, 0.0f, 1.0f);
                ImGui::SliderFloat("Quadratic", &spotQuad, 0.0f, 1.0f);
                ImGui::SliderFloat("CutOff", &spotCutoff, 0.0f, 1.0f);
                ImGui::SliderFloat("OuterCutOff", &spotOuterCutoff, 0.0f, 1.0f);
            }

            ImGui::SliderFloat("Shininess", &shininess, 1.0f, 256.0f);
            ImGui::SliderFloat("Light Intensity", &lightIntensity, 0.0f, 10.0f);

            const char* modelNames[] = { "Castle", "Home" };
            ImGui::Combo("Model", &currentModelIndex, modelNames, IM_ARRAYSIZE(modelNames));
            ImGui::End();
        }
        pointLightPositions[0] = lightPos;

        // Clear screen
        glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Activate shader
        lightingShader.use();
        lightingShader.setFloat("lightIntensity", lightIntensity);
        lightingShader.setBool("useDirLight", useDirLight);
        lightingShader.setBool("usePointLights", usePointLights);
        lightingShader.setBool("useSpotLight", useSpotLight);
        lightingShader.setFloat("shininess", shininess);

        lightingShader.setVec3("dirLight.direction", dirLightDir);
        lightingShader.setVec3("dirLight.ambient", dirLightAmbient);
        lightingShader.setVec3("dirLight.diffuse", dirLightDiffuse);
        lightingShader.setVec3("dirLight.specular", dirLightSpecular);

        lightingShader.setVec3("pointLights[0].position", pointLightPos);
        lightingShader.setVec3("pointLights[0].ambient", pointLightAmbient);
        lightingShader.setVec3("pointLights[0].diffuse", pointLightDiffuse);
        lightingShader.setVec3("pointLights[0].specular", pointLightSpecular);
        lightingShader.setFloat("pointLights[0].constant", pointConst);
        lightingShader.setFloat("pointLights[0].linear", pointLinear);
        lightingShader.setFloat("pointLights[0].quadratic", pointQuad);

        lightingShader.setVec3("spotLight.position", camera.Position);
        lightingShader.setVec3("spotLight.direction", camera.Front);
        lightingShader.setVec3("spotLight.ambient", spotLightAmbient);
        lightingShader.setVec3("spotLight.diffuse", spotLightDiffuse);
        lightingShader.setVec3("spotLight.specular", spotLightSpecular);
        lightingShader.setFloat("spotLight.constant", spotConst);
        lightingShader.setFloat("spotLight.linear", spotLinear);
        lightingShader.setFloat("spotLight.quadratic", spotQuad);
        lightingShader.setFloat("spotLight.cutOff", spotCutoff);
        lightingShader.setFloat("spotLight.outerCutOff", spotOuterCutoff);

        // View/projection matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        lightingShader.setVec3("viewPos", camera.Position);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, modelPosition);
        model = glm::scale(model, glm::vec3(modelScale));
        if (currentModelIndex == 0) {
            model = glm::rotate(model, glm::radians(modelRotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(modelRotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(modelRotation.z), glm::vec3(0, 0, 1));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        else if (currentModelIndex == 1) {
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        lightingShader.setMat4("model", model);
        lightingShader.setInt("material.diffuse", 0);
        lightingShader.setInt("material.specular", 1);

        // Draw model
        if (currentModelIndex == 0) {
            for (auto& mesh : castleModel.meshes) {
                mesh.textures.clear();

                for (int i = 0; i < textureIDs.size(); ++i) {
                    glActiveTexture(GL_TEXTURE0 + i);
                    glBindTexture(GL_TEXTURE_2D, textureIDs[i]);

                    Texture tex;
                    tex.id = textureIDs[i];
                    tex.type = "texture_diffuse"; 
                    tex.path = texturePaths[i];  
                    mesh.textures.push_back(tex);

                    std::string uniformName = "texture" + std::to_string(i + 1);
                    lightingShader.setInt(uniformName.c_str(), i);
                }
            }

            castleModel.Draw(lightingShader);
        }
        else if (currentModelIndex == 1) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sceneTextures[0]); 

            static unsigned int whiteTex = createWhiteTexture();
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, whiteTex);

            sceneModel.Draw(lightingShader);
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
