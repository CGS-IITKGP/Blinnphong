cmake_minimum_required(VERSION 3.10)
project(Blinnphong)

set(CMAKE_CXX_STANDARD 17)

# Add source files
set(SOURCES
    main.cpp
    light_main.cpp
    camera.cpp
    imgui.cpp
    imgui_draw.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    mesh.cpp
    model.cpp
    mouse.cpp
    processInput.cpp
    shaderclass.cpp
    src/glad.c   #Add glad.c explicitly
)

# Add executable
add_executable(Blinnphong ${SOURCES})

# Find packages (glfw3 and glm from vcpkg)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

find_package(assimp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)

# Debug: Check if Assimp target is found
if(TARGET assimp::assimp)
    message(STATUS "Assimp target found")
else()
    message(WARNING "Assimp target NOT found")
endif()

# Include directories
target_include_directories(Blinnphong PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/Release)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Release)
