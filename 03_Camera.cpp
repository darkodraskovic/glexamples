#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Shader.h"
#include "Cube.h"
#include "zzz.h"

int main()
{
    // Application init
    // ---------------------------------------------------------------------------    
    Application app;
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    // Application CONTENT
    // ---------------------------------------------------------------------------
    
    Shader vColShader( "../shaders/VCol.vs", "../shaders/VCol.fs");
    Cube cube1(vColShader);
    app.models_.push_back(&cube1);

    Cube cube2(vColShader);
    cube2.Translate(-zzz::ONE);
    app.models_.push_back(&cube2);

    Cube cube3(vColShader);
    cube3.Translate(zzz::ONE);
    app.models_.push_back(&cube3);

    app.camera_.position_.z = 7.0f;
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
