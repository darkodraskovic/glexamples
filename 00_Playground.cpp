// cd build/ && make && ./main
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Shader.h"

using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Shader
    Shader shader(
        "/home/darko/Radovi/AppDev/OpenGL/shaders/vs.glsl",
        "/home/darko/Radovi/AppDev/OpenGL/shaders/fs.glsl");
    
    // Textures
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;

    const char* file_name = "/home/darko/Radovi/AppDev/OpenGL/assets/container.jpg";
    unsigned char *textureData0 = stbi_load(file_name, &width, &height, &nrChannels, 0);
    if (!textureData0) {
        std::cout << "Failed to load texture 0" << std::endl;
        exit(1);
    }
    unsigned int texture0;
    glGenTextures(1, &texture0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData0);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData0);

    file_name = "/home/darko/Radovi/AppDev/OpenGL/assets/awesomeface.png";
    unsigned char *textureData1 = stbi_load(file_name, &width, &height, &nrChannels, 0);
    if (!textureData1) {
        std::cout << "Failed to load texture 1" << std::endl;
        exit(1);
    }    
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData1);
    
    // first triangle
    float vertices[] = {    
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // left bottom
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // left top
        0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // right top  
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   1.0f, 0.0f    // right bottom    
    };

    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
    0, 2, 3    // second triangle
    };
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader.use();
    shader.setInt(("texture0"), 0);
    shader.setInt(("texture1"), 1);
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        
        float timeValue = glfwGetTime();
        float sinValue = sin(timeValue);
        float normValue = (sinValue / 2.0f) + 0.5f;

        vec4 color = vec4(0.5f, normValue, 0.5f, 1.0f);
        mat4 transform = mat4(1.0f);
        // vec3 tr = vec3(sinValue, 0, 0);
        // vec3 sc = vec3(sinValue, sinValue, sinValue);
        // float angle = sinValue * 2 * M_PI;
        // vec3 axis = vec3(0, 0, 1);
        // transform = translate(transform, tr);
        // transform = scale(transform, sc);
        // transform = rotate(transform, angle, axis);
        
        shader.setVec4("uColor", color);        
        shader.setMat4("uTransform", transform);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
