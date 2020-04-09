#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application.h"
#include "Camera.h"

namespace mouseData
{
    float lastMouseX = SCR_WIDTH/2, lastMouseY = SCR_HEIGHT/2;
    float mouseOffsetX, mouseOffsetY;
    float mouseScrollY;
    bool firstMouse = true;
    bool processMouseMovement = false;
    bool processMouseScroll = false;
}

using namespace glm;
using namespace mouseData;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double posX, double posY);
void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY);
    
Application::Application() {};

int Application::Init()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window_ = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Camera", NULL, NULL);

    if (window_ == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);

    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window_, MouseCallback);

    glfwSetScrollCallback(window_, ScrollCallback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    return 0;
};


void Application::ProcessInput(float deltaTime)
{
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_, true);
    
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
        camera_.ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
        camera_.ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
        camera_.ProcessKeyboard(CAM_LEFT, deltaTime);
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
        camera_.ProcessKeyboard(CAM_RIGHT, deltaTime);
    if (glfwGetKey(window_, GLFW_KEY_E) == GLFW_PRESS)
        camera_.ProcessKeyboard(CAM_UP, deltaTime);
    if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS)
        camera_.ProcessKeyboard(CAM_DOWN, deltaTime);

    if (processMouseMovement) {
        camera_.ProcessMouseMovement(mouseOffsetX, mouseOffsetY);    
        processMouseMovement = false;
    }

    if (processMouseScroll) {
        camera_.ProcessMouseScroll(mouseScrollY);
        processMouseScroll = false;
    }
}

float cameraYaw = -90, cameraPitch = 0, cameraFov = 45.0f;

void Application::Render(float deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera_.GetViewMatrix();
    glm::mat4 projection = camera_.GetProjectionMatrix(SCR_WIDTH, SCR_HEIGHT);

    for(std::vector<std::shared_ptr<Entity>>::iterator it = entities_.begin(); it != entities_.end(); ++it) {
        (*it)->Update(deltaTime);
        (*it)->Draw(deltaTime, view, projection);
    }
        
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

float Application::GetDeltaTime()
{
    return glfwGetTime() - lastFrame_;
};

void Application::Update()
{
    float currentFrame = glfwGetTime();
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;
    
    ProcessInput(deltaTime_);
    Render(deltaTime_);
};

bool Application::ShouldClose()
{
    return glfwWindowShouldClose(window_);    
};
void Application::Terminate()
{
    glfwTerminate();
};

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void MouseCallback(GLFWwindow* window, double posX, double posY)
{
    if (firstMouse) {
        lastMouseX = posX;
        lastMouseY = posY;
        firstMouse = false;
    }

    mouseOffsetX = posX - lastMouseX;
    mouseOffsetY = posY - lastMouseY;
    lastMouseX = posX;
    lastMouseY = posY;

    processMouseMovement = true;    
};

void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY)
{
    mouseScrollY = offsetY;
    processMouseScroll = true;
}
