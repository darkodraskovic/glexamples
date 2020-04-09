#include "Material.h"

using namespace glm;

Material::Material()
{
};

Material::Material(std::shared_ptr<Shader> shader)
{
    shader_ =  shader;
};

void Material::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    shader_->use();

    shader_->setMat4("uModel", model);
    shader_->setMat4("uView", view);
    shader_->setMat4("uProjection", projection);
}
