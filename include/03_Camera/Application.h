#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Model.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Application
{
public:
    Application();
    int Init();
    void ProcessInput(float deltaTime);
    void Render(float deltaTime);
    void Update();
    bool ShouldClose();
    void Terminate();

    std::vector<Model*> models_;
    GLFWwindow* window_;
};

#endif
