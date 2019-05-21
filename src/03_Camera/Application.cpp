#include <iostream>

#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#include "Application.h"

using namespace glm;

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = SCR_WIDTH/2, lastY = SCR_HEIGHT/2;
float cameraYaw = 0, cameraPitch = 0, cameraFov = 45.0f;
bool firstMouse = false;

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

    float cameraSpeed = deltaTime * 10;
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
    if (glfwGetKey(window_, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;    
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos += cameraSpeed * normalize(cross(cameraUp, cameraFront));
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos -= cameraSpeed * normalize(cross(cameraUp, cameraFront));
}

void Application::Render(float deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 view = mat4(1.0f);
    cameraFront.x = cos(radians(cameraYaw)) * cos(radians(cameraPitch));
    cameraFront.y = sin(radians(cameraPitch));
    cameraFront.z = sin(radians(cameraYaw)) * cos(radians(cameraPitch));
    view = lookAt(cameraPos, cameraPos + normalize(cameraFront), cameraUp);
    
    mat4 projection;
    projection = perspective(radians(cameraFov), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

    for(std::vector<Model*>::iterator it = models_.begin(); it != models_.end(); ++it) {
        (*it)->Update(deltaTime);
        (*it)->Draw(view, projection);
    }
        
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void Application::Update()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    ProcessInput(deltaTime);
    Render(deltaTime);
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
        lastX = posX;
        lastY = posY;
    }

    float offsetX = posX - lastX;
    float offsetY = posY - lastY;
    lastX = posX;
    lastY = posY;

    float sensitivity = 0.05;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    cameraYaw  += offsetX;
    cameraPitch -= offsetY;

    cameraPitch = glm::clamp(cameraPitch, -89.0f, 89.0f);
};

void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY)
{
    cameraFov -= offsetY * 2;
    cameraFov = clamp(cameraFov, 1.0f, 45.0f);
}
