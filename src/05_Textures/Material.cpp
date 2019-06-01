#include "Material.h"

using namespace glm;

Material::Material()
{
};

Material::Material(Shader* shader)
{
    shader_ = shader;
};

Material::Material(Shader* shader, const std::string& type)
{
    shader_ = shader;
    if (type == "Phong") {
        phong_ = new material::Phong();
    }
    else if (type == "PhongMap") {
        phongMap_ = new material::PhongMap();
    }
};

void Material::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    shader_->use();

    shader_->setMat4("uModel", model);
    shader_->setMat4("uView", view);
    shader_->setMat4("uProjection", projection);

    if (phong_) {
        shader_->setVec3("uMaterial.ambient",  phong_->ambient);
        shader_->setVec3("uMaterial.diffuse",  phong_->diffuse);
        shader_->setVec3("uMaterial.specular", phong_->specular);
        shader_->setFloat("uMaterial.shininess", phong_->shininess);
    }
    else if (phongMap_) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, phongMap_->diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, phongMap_->specular);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, phongMap_->emissive);

        shader_->setInt("uMaterial.diffuse", 0);
        shader_->setInt("uMaterial.specular", 1);
        shader_->setInt("uMaterial.emissive", 2);
        shader_->setFloat("uMaterial.shininess", phongMap_->shininess);
    }
}

