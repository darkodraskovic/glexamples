#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Model
{
 public:
    Model(const Shader& shader);
    void Draw(const glm::mat4& uView, const glm::mat4& uProjection);
    void SetVertices(glm::vec3* vertices, int vLen, int numAttrs);
    void SetIndices(unsigned int* indices, int iLen);
    void GenerateModel();
    
    void SetRotation(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& scale);
    void SetTranslation(const glm::vec3& translation);
    virtual void Update(float time);
    
    const Shader& shader_;
    unsigned int VAO_;
 private:
    int vLen_;
    int numAttrs_;
    int iLen_;

    glm::mat4 id_;
    glm::mat4 rotation_;
    glm::mat4 scale_;
    glm::mat4 translation_;
    glm::mat4 transform_;
    
    glm::vec3* vertices_;
    unsigned int* indices_;

};

#endif
