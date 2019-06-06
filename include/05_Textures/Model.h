#ifndef MODEL_H
#define MODEL_H

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

class Model
{
 public:
    Model();
    ~Model();

    void SetVertices(glm::vec3 vertices[], int numVerts, int numAttrs);
    void SetVertices(glm::vec4 vertices[], int numVerts, int numAttrs);
    void SetVertices(float vertices[], int numVerts, int numAttrs, int attrSize);
    void SetIndices(unsigned int indices[], int numIdx);
    virtual void GenerateModel();
    void Copy(std::shared_ptr<Model> model);
    
    void SetRotation(float angle, const glm::vec3& axis);
    void Rotate(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& scale);
    void SetScale(float scale);
    void Scale(const glm::vec3& scale);
    void Scale(float scale);    
    void SetTranslation(const glm::vec3& translation);
    void Translate(const glm::vec3& translation);
    
    void Render(float deltaTime, const glm::mat4& uView, const glm::mat4& uProjection);
    virtual void Update(float deltaTime);
    
    unsigned int VAO_;
    unsigned int VBO_;
    unsigned int EBO_;
    
    std::shared_ptr<Material> material_;
    
 private:
    void InitTransform_();
    void SetVertices_(float vertices[], int numVerts, int numAttrs);
    
    int numVerts_;
    int numAttrs_;
    int numIdx_;
    size_t attrSize_;
    size_t vertSize_;

    glm::mat4 id_;
    glm::mat4 rotation_;
    glm::mat4 scale_;
    glm::mat4 translation_;
    glm::mat4 transform_;

    std::shared_ptr<float []> vertices_;
    std::shared_ptr<unsigned int []> indices_;
};

#endif
