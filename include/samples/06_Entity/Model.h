#ifndef MODEL_H
#define MODEL_H

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
    void Generate();
    void Copy(Model* model);

    void Render();

    unsigned int VAO_;
    unsigned int VBO_;
    unsigned int EBO_;

private:
    void SetVertices_(float vertices[], int numVerts, int numAttrs);

    int numVerts_;
    int numAttrs_;
    int numIdx_;
    size_t attrSize_;
    size_t vertSize_;

    std::shared_ptr<float []> vertices_;
    std::shared_ptr<unsigned int []> indices_;
};

#endif
