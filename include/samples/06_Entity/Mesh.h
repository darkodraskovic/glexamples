#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Material.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    // interleaved VBO
    void GenArrayBuffer(float vertices[], int elemPerAttr, int numVerts, int numAttrs);

    // separate VBOs
    void GenArrayBuffer(float attribArray[], int elemPerAttr, int numVerts);

    // indices - EBO
    void GenElementBuffer(unsigned int indices[], int numIdx);

    void Render();

    unsigned int VAO_;
    unsigned int VBO_;
    std::vector<unsigned int> VBOs_;    
    unsigned int EBO_;

	GLenum mode_ = GL_TRIANGLES;
    
private:
    int numVerts_ = 0;
    int numIdx_ = 0;
};

#endif
