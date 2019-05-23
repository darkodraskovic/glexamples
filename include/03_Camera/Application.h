#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Model.h"
#include "Camera.h"

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
    Camera camera_;

    float deltaTime_ = 0.0f;	// Time between current frame and last frame
    float lastFrame_ = 0.0f; // Time of last frame
};

#endif
