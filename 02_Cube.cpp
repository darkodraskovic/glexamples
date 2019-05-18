#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "cc.h"
#include "Model.h"

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int genModel(float* vertices, int vLen, unsigned int* indices, int iLen, int stride);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
    
    Shader shader( "../shaders/Model.vs", "../shaders/Model.fs");

    // cube
    // ----
    vec3 frontBL(-0.5f, -0.5f, 0.5f);
    vec3 frontTL(-0.5f, 0.5f, 0.5f);
    vec3 frontTR(0.5f, 0.5f, 0.5f);
    vec3 frontBR(0.5f, -0.5f, 0.5f);
    vec3 backBL = frontBL + cc::BACK;
    vec3 backTL = frontTL + cc::BACK;
    vec3 backTR = frontTR + cc::BACK;
    vec3 backBR = frontBR + cc::BACK;

    vec3 vertices[] = {
        // front
        frontBL, cc::RED, frontBR, cc::GREEN, frontTR, cc::BLUE, frontTL, cc::MAGENTA,
        // back
        backBR, cc::RED, backBL, cc::GREEN, backTL, cc::BLUE, backTR, cc::CYAN,
        // left
        backBL, cc::RED, frontBL, cc::GREEN, frontTL, cc::BLUE, backTL, cc::MAGENTA,
        // right
        frontBR, cc::RED, backBR, cc::GREEN, backTR, cc::BLUE, frontTR, cc::CYAN,          
    };
    int vLen = 16;
    
    unsigned int indices[] = {
        // front
        0, 1, 2,
        0, 2, 3,
        // back
        4, 5, 6,
        4, 6, 7,
        // left
        8, 9, 10,
        8, 10, 11,
        // left
        12, 13, 14,
        12, 14, 15,
    };
    int iLen = sizeof(indices)/sizeof(indices[0]);

    Model cube(vertices, vLen, indices, iLen, shader);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = glfwGetTime();
        
        cube.SetRotation(time*100, cc::ONE);
        // cube.SetScale(vec3(glm::sin(time), 1.0f, 1.0f));
        // cube.SetTranslation(vec3(0.0f, glm::sin(time), 1.0f));
        
        mat4 view = mat4(1.0f);
        view = translate(view, vec3(0.0f, 0.0f, -6.0f));
        mat4 projection;
        projection = perspective(radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

        cube.Draw(view, projection);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
