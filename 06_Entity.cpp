#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Material.h"
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
    
    auto litSolidTexturedShader = std::shared_ptr<Shader>(
        new Shader( "../shaders/LitSolidTextured.vs", "../shaders/LitSolidTextured.fs"));

    auto material = std::shared_ptr<Material>(new Material(litSolidTexturedShader, "PhongMap"));
    auto cube2 = std::make_shared<Cube>(material);
    cube2->material_->phongMap_->diffuse = diffuseMetal;
    cube2->material_->phongMap_->specular = specularMetal;
    cube2->material_->phongMap_->emissive = emissiveMetal;
    cube2->material_->phongMap_->shininess = 1024.0f;
    cube2->SetScale(2);
    app.entities_.push_back(cube2);

    material = std::shared_ptr<Material>(new Material(litSolidTexturedShader, "PhongMap"));    
    auto cube4 = std::make_shared<Cube>(material);
    cube4->material_->phongMap_->diffuse = diffuseBricks;
    cube4->material_->phongMap_->specular = specularBricks;
    cube4->material_->phongMap_->emissive = emissiveBricks;
    cube4->material_->phongMap_->shininess = 128.0f;
    cube4->Translate(zzz::ONE*2.0f);
    cube4->Scale(2);
    app.entities_.push_back(cube4);
    
    litSolidTexturedShader->use();
    litSolidTexturedShader->setVec3("uLight.ambient",  zzz::DARK_GRAY);
    litSolidTexturedShader->setVec3("uLight.diffuse",  zzz::GRAY);
    litSolidTexturedShader->setVec3("uLight.specular", zzz::GRAY);
    litSolidTexturedShader->setVec3("uLight.position", 0.5f, 0.0f, 5.0f);

    app.camera_.position_.z = 12.0f;
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {

        float time = glfwGetTime();
        float sinVal = glm::sin(time);
        float cosVal = glm::cos(time);
        vec3 col = vec3(cosVal, 0.0f, sinVal);
        litSolidTexturedShader->use();
        litSolidTexturedShader->setVec3("uLight.position", col*5.0f);
        
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
