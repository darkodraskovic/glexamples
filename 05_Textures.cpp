#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Material.h"
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
    
    unsigned int diffuseBricks = app.resourceManager_.LoadTexture("../assets/bricks_diffuse.jpg");
    unsigned int specularBricks = app.resourceManager_.LoadTexture("../assets/bricks_specular.jpg");
    unsigned int emissiveBricks = app.resourceManager_.LoadTexture("../assets/bricks_emissive_green.png");
    unsigned int diffuseMetal = app.resourceManager_.LoadTexture("../assets/metal_diffuse.jpg");
    unsigned int specularMetal = app.resourceManager_.LoadTexture("../assets/metal_specular.jpg");
    unsigned int emissiveMetal = app.resourceManager_.LoadTexture("../assets/metal_emissive_red.png");
    
    auto litSolidShader = std::shared_ptr<Shader>(
        new Shader( "../shaders/LitSolid.vs", "../shaders/LitSolid.fs"));
    auto litSolidTexturedShader = std::shared_ptr<Shader>(
        new Shader( "../shaders/LitSolidTextured.vs", "../shaders/LitSolidTextured.fs"));

    auto cube2 = std::make_shared<Cube>();
    cube2->GenerateModel();
    cube2->material_ = std::shared_ptr<Material>(new Material(litSolidTexturedShader, "PhongMap"));
    cube2->material_->phongMap_->diffuse = diffuseMetal;
    cube2->material_->phongMap_->specular = specularMetal;
    cube2->material_->phongMap_->emissive = emissiveMetal;
    cube2->material_->phongMap_->shininess = 1024.0f;
    cube2->SetScale(2);
    app.models_.push_back(cube2);

    auto cube3 = std::make_shared<Cube>();
    cube3->Copy(cube2.get());
    cube3->Translate(-zzz::ONE*2.0f);
    cube3->Scale(2);
    app.models_.push_back(cube3);
    
    auto cube4 = std::make_shared<Cube>();
    cube4->Copy(cube3.get());
    cube4->material_ = std::shared_ptr<Material>(new Material(litSolidTexturedShader, "PhongMap"));
    cube4->material_->phongMap_->diffuse = diffuseBricks;
    cube4->material_->phongMap_->specular = specularBricks;
    cube4->material_->phongMap_->emissive = emissiveBricks;
    cube4->material_->phongMap_->shininess = 128.0f;
    cube4->Translate(zzz::ONE*2.0f);
    cube4->Scale(2);
    app.models_.push_back(cube4);
    
    app.camera_.position_.z = 12.0f;
    
    // Light
    litSolidShader->use();
    litSolidShader->setVec3("uLight.ambient",  0.2f, 0.2f, 0.2f);
    litSolidShader->setVec3("uLight.diffuse",  0.5f, 0.5f, 0.5f);
    litSolidShader->setVec3("uLight.specular", 1.0f, 1.0f, 1.0f);
    litSolidShader->setVec3("uLight.position", 0.5f, 0.0f, 5.0f);

    litSolidTexturedShader->use();
    litSolidTexturedShader->setVec3("uLight.ambient",  zzz::DARK_GRAY);
    litSolidTexturedShader->setVec3("uLight.diffuse",  zzz::GRAY);
    litSolidTexturedShader->setVec3("uLight.specular", zzz::GRAY);
    litSolidTexturedShader->setVec3("uLight.position", 0.5f, 0.0f, 5.0f);
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {

        litSolidShader->use();
        litSolidShader->setVec3("uViewPos", app.camera_.position_);
        litSolidTexturedShader->use();
        litSolidTexturedShader->setVec3("uViewPos", app.camera_.position_);
        
        // float time = glfwGetTime();
        // float sinVal = glm::sin(time);
        // float cosVal = glm::cos(time);
        // vec3 col = vec3(cosVal, 0.0f, sinVal);
        // litSolidShader->use();
        // litSolidShader->setVec3("uLight.position", col*5.0f);
        // litSolidTexturedShader->use();
        // litSolidTexturedShader->setVec3("uLight.position", col*5.0f);
        
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
