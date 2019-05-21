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

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

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

    float cameraSpeed = deltaTime * 7;
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
    view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    
    mat4 projection;
    projection = perspective(radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

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
