#ifndef ENTITY_H
#define ENTITY_H

#include "Mesh.h"
#include "Material.h"

class Entity
{
public:
    Entity();
    
    void SetRotation(float angle, const glm::vec3& axis);
    void Rotate(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& scale);
    void SetScale(float scale);
    void Scale(const glm::vec3& scale);
    void Scale(float scale);    
    void SetTranslation(const glm::vec3& translation);
    void Translate(const glm::vec3& translation);

    virtual void Update(float deltaTime);
    virtual void Draw (float deltaTime, const glm::mat4& uView, const glm::mat4& uProjection);

    std::shared_ptr<Material> material_;
    std::shared_ptr<Mesh> mesh_;
    
private:
    glm::mat4 id_;
    glm::mat4 rotation_;
    glm::mat4 scale_;
    glm::mat4 translation_;
    glm::mat4 transform_;
};

#endif
