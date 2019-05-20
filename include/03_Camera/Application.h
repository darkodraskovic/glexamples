#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Application
{
public:
    Application();
    int Init();
    void ProcessInput(GLFWwindow *window);
};

#endif
