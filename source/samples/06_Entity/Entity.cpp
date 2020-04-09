#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>

Entity::Entity()
{
    mesh_ = std::shared_ptr<Mesh>(new Mesh());
    
    id_ = glm::mat4(1.0f);
    rotation_ = glm::mat4(1.0f);
    scale_ = glm::mat4(1.0f);
    translation_ = glm::mat4(1.0f);
    transform_ = glm::mat4(1.0f);
};

void Entity::SetRotation(float angle, const glm::vec3& axis)
{
    rotation_ = glm::rotate(id_, glm::radians(angle), axis);
}

void Entity::Rotate(float angle, const glm::vec3& axis)
{
    rotation_ = glm::rotate(rotation_, glm::radians(angle), axis);
}

void Entity::SetScale(const glm::vec3& scale)
{
    scale_ = glm::scale(id_, scale);
}

void Entity::SetScale(float scale)
{
    scale_ = glm::scale(id_, glm::vec3(scale));
}

void Entity::Scale(const glm::vec3& scale)
{
    scale_ = glm::scale(scale_, scale);
}

void Entity::Scale(float scale)
{
    scale_ = glm::scale(scale_, glm::vec3(scale));
}

void Entity::SetTranslation(const glm::vec3& translation)
{
    translation_ = glm::translate(id_, translation);
}

void Entity::Translate(const glm::vec3& translation)
{
    translation_ = glm::translate(translation_, translation);
}

void Entity::Update(float deltaTime)
{
}

void Entity::Draw(float deltaTime, const glm::mat4& uView, const glm::mat4& uProjection)
{
    material_->Update(deltaTime, translation_* rotation_ * scale_, uView, uProjection);
    mesh_->Render();
}
