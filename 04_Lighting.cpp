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
    
    Shader* litSolidShader = new Shader ( "../shaders/LitSolid.vs", "../shaders/LitSolid.fs");
    
    Cube* cube1 = new Cube();
    cube1->shader_ = litSolidShader;
    cube1->GenerateModel();
    zzz::PhongMaterial* mat1 = new zzz::PhongMaterial();
    mat1->diffuse = zzz::RED;
    cube1->material_ = mat1;
    cube1->SetScale(2);
    app.models_.push_back(cube1);

    Cube* cube2 = new Cube();
    cube2->Clone(cube1);
    zzz::PhongMaterial* mat2 = new zzz::PhongMaterial();
    mat2->shininess = 512;
    mat2->diffuse = zzz::GREEN;
    cube2->material_ = mat2;    
    cube2->Translate(-zzz::ONE*2.0f);
    cube2->Scale(2);
    app.models_.push_back(cube2);

    Cube* cube3 = new Cube();
    cube3->Clone(cube1);
    zzz::PhongMaterial* mat3 = new zzz::PhongMaterial();
    mat3->shininess = 128;
    mat3->diffuse = zzz::BLUE;
    cube3->material_ = mat3;    
    cube3->Translate(zzz::ONE);
    app.models_.push_back(cube3);
    
    app.camera_.position_.z = 7.0f;

    // Light
    litSolidShader->use();
    litSolidShader->setVec3("uLight.ambient",  0.2f, 0.2f, 0.2f);
    litSolidShader->setVec3("uLight.diffuse",  0.5f, 0.5f, 0.5f);
    litSolidShader->setVec3("uLight.specular", 1.0f, 1.0f, 1.0f);
    litSolidShader->setVec3("uLight.position", 2.0f, -0.5f, 9.0f);
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {

        litSolidShader->use();
        litSolidShader->setVec3("uViewPos", app.camera_.position_);
                
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
