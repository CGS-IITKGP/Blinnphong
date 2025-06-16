#pragma once
#include <GLFW/glfw3.h>

// Declare the callbacks
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// If you need to access camera or other variables, you may need to declare them as extern here
extern float lastX, lastY;
extern bool firstMouse;
