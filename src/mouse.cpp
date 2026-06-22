#include "camera.h" // Include your camera header if needed
#include "mouse.h"
#include <glm/glm.hpp>

// These should match the externs in the header
float lastX = 400, lastY = 300;
bool firstMouse = true;

// You must have a Camera instance accessible here
extern Camera camera;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
