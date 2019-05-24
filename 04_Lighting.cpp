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
    
    Shader litDiffShader( "../shaders/LitDiff.vs", "../shaders/LitDiff.fs");
    
    Cube cube1(litDiffShader, zzz::RED);
    app.models_.push_back(&cube1);

    Cube cube2(litDiffShader, zzz::GREEN);
    cube2.Translate(-zzz::ONE);
    app.models_.push_back(&cube2);

    Cube cube3(litDiffShader, zzz::BLUE);
    cube3.Translate(zzz::ONE);
    app.models_.push_back(&cube3);

    app.camera_.position_.z = 7.0f;
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        litDiffShader.setVec3("uLightColor", zzz::WHITE);
        litDiffShader.setVec3("uAmbientColor", zzz::BLACK);
        litDiffShader.setVec3("uLightDirection", vec3(0.30, 1.0, 0.70));
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
