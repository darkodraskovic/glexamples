#include "PhongMap.h"

PhongMap::PhongMap(std::shared_ptr<Shader> shader) : Material(shader)
{
}

void PhongMap::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    Material::Update(deltaTime, model, view, projection);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specular_);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, emissive_);

    shader_->setInt("uMaterial.diffuse", 0);
    shader_->setInt("uMaterial.specular", 1);
    shader_->setInt("uMaterial.emissive", 2);
    shader_->setFloat("uMaterial.shininess", shininess_);
}
