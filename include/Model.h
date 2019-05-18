#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

using namespace glm;

class Model
{
 public:
    Model(float* vertices, int vLen, unsigned int* indices, int iLen, int stride, const Shader& shader);
    void Draw(const glm::mat4& uView, const glm::mat4& uProjection);
    void SetVertices(float* vertices, int vLen);
    void SetIndices(float* indices, int iLen);
    void SetRotation(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& scale);
    void SetTranslation(const glm::vec3& translation);
    
    const Shader& shader_;
    unsigned int VAO_;
    
 private:
    int vLen_;
    int iLen_;

    mat4 id_;
    mat4 rotation_;
    mat4 scale_;
    mat4 translation_;
    mat4 transform_;
    
    float* vertices_;
    unsigned int* indices_;
};

#endif
