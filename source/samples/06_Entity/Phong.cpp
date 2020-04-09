#include "Phong.h"

Phong::Phong(std::shared_ptr<Shader> shader) : Material(shader)
{
}

void Phong::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    Material::Update(deltaTime, model, view, projection);
    
    shader_->setVec3("uMaterial.ambient",  ambient_);
    shader_->setVec3("uMaterial.diffuse",  diffuse_);
    shader_->setVec3("uMaterial.specular", specular_);
    shader_->setFloat("uMaterial.shininess", shininess_);
}
