#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

class Model
{
 public:
    Model();
    Model* Clone(Model* model);
    void Draw(float deltaTime, const glm::mat4& uView, const glm::mat4& uProjection);
    void SetVertices(glm::vec3* vertices, int vLen, int numAttrs);
    void SetVertices(glm::vec4* vertices, int vLen, int numAttrs);
    void SetIndices(unsigned int* indices, int iLen);
    virtual void GenerateModel();
    void InitTransform();
    
    void SetRotation(float angle, const glm::vec3& axis);
    void Rotate(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& scale);
    void SetScale(float scale);
    void Scale(const glm::vec3& scale);
    void Scale(float scale);    
    void SetTranslation(const glm::vec3& translation);
    void Translate(const glm::vec3& translation);
    
    virtual void Update(float deltaTime);
    
    Material* material_;
    unsigned int VAO_;
    
 private:
    int vLen_;
    int numAttrs_;
    int iLen_;
    size_t vAttrSize_;
    size_t vSize_;

    glm::mat4 id_;
    glm::mat4 rotation_;
    glm::mat4 scale_;
    glm::mat4 translation_;
    glm::mat4 transform_;
    
    glm::vec3* vertices3_;
    glm::vec4* vertices4_;
    unsigned int* indices_;
};

#endif
