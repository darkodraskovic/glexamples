#ifndef MODEL_H
#define MODEL_H

#include <vector> 
#include "Material.h"

class Model
{
public:
    Model();
    ~Model();

    void SetVertices(glm::vec3 vertices[], int numVerts, int numAttrs);
    void SetVertices(glm::vec4 vertices[], int numVerts, int numAttrs);
    void SetVertices(float vertices[], int numVerts, int numAttrs, int elemPerAttr);
    void SetIndices(unsigned int indices[], int numIdx);

    void GenArrayBuffer(const float attribArray[], int elemPerAttr, int numVerts);
    void GenElementBuffer(unsigned int indices[], int numIdx);
    
    void Generate();

    void Render();

    unsigned int VAO_;
    unsigned int VBO_;
    unsigned int EBO_;

	GLenum mode_ = GL_TRIANGLES;
    
private:
    void SetVertices_(float vertices[], int numVerts, int numAttrs);

    int numVerts_;
    int numAttrs_;
    int numIdx_;
    size_t attrSize_;
    size_t vertSize_;

    std::shared_ptr<float []> vertices_;
    std::shared_ptr<unsigned int []> indices_;

    std::vector<unsigned int> VBOs_;
};

#endif
