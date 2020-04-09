#include "Mesh.h"

Mesh::Mesh()
{
    glGenVertexArrays(1, &VAO_);
}

// VBO

void Mesh::GenArrayBuffer(float vertices[], int elemPerAttr, int numVerts, int numAttrs)
{
    numVerts_ = numVerts;
    
    glBindVertexArray(VAO_);

    // VBO
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    size_t attrSize = elemPerAttr * sizeof(float);
    int size = attrSize * numAttrs * numVerts;
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    for (int i = 0; i < numAttrs; ++i) {
        glVertexAttribPointer(i, elemPerAttr, GL_FLOAT, GL_FALSE, attrSize, (void*)(i*attrSize));
        glEnableVertexAttribArray(i);
    }

    glBindVertexArray(0);
}

// VBOs

void Mesh::GenArrayBuffer(float attribArray[], int elemPerAttr, int numVerts)
{
    numVerts_ = numVerts;
    
    // VAO
    glBindVertexArray(VAO_);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs_.push_back(VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    int size = sizeof(float) * elemPerAttr * numVerts_;
    glBufferData(GL_ARRAY_BUFFER, size, attribArray, GL_STATIC_DRAW);
    int idx = VBOs_.size()-1;
    glVertexAttribPointer(idx, elemPerAttr, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(idx);

    glBindVertexArray(0);
}

// EBO

void Mesh::GenElementBuffer(unsigned int indices[], int numIdx)
{
    numIdx_ = numIdx;
    
    // VAO
    glBindVertexArray(VAO_);
    
    glGenBuffers(1, &EBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    int size = sizeof(unsigned int) * numIdx_;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

// RENDER

void Mesh::Render()
{
    glBindVertexArray(VAO_);
    
    if (numIdx_) {
        glDrawElements(mode_, numIdx_, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(mode_, 0, numVerts_);
    }
    
    glBindVertexArray(0);
}

// DESTRUCTOR

Mesh::~Mesh()
{
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
    glDeleteBuffers(VBOs_.size(), &VBOs_.front());
    glDeleteVertexArrays(1, &VAO_);
};
