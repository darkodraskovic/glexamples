#include "Model.h"

Model::Model()
{
    glGenVertexArrays(1, &VAO_);
}

// INTERLEAVED arrays

void Model::SetVertices(glm::vec3 vertices[], int numVerts, int numAttrs)
{
    attrSize_ = sizeof(glm::vec3);
    SetVertices_((float*)vertices, numVerts, numAttrs);
}

void Model::SetVertices(glm::vec4 vertices[], int numVerts, int numAttrs)
{
    attrSize_ = sizeof(glm::vec4);
    SetVertices_((float*)vertices, numVerts, numAttrs);
}

void Model::SetVertices(float vertices[], int numVerts, int numAttrs, int elemPerAttr)
{
    attrSize_ = elemPerAttr * sizeof(float);
    SetVertices_(vertices, numVerts, numAttrs);
}

void Model::SetVertices_(float vertices[], int numVerts, int numAttrs)
{
    vertices_ = std::shared_ptr<float []>(vertices);
    numVerts_ = numVerts;
    numAttrs_ = numAttrs;
    vertSize_ = numAttrs_ * attrSize_;    
}

void Model::SetIndices(unsigned int indices[], int numIdx)
{
    indices_ = std::shared_ptr<unsigned int []>(indices);
    numIdx_ = numIdx;
}

void Model::Generate()
{
    // VAO
    glBindVertexArray(VAO_);

    // VBO
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, numVerts_ * vertSize_, vertices_.get(), GL_STATIC_DRAW);
    for (int i = 0; i < numAttrs_; ++i) {
        glVertexAttribPointer(
            i, attrSize_ / sizeof(float), GL_FLOAT, GL_FALSE, vertSize_, (void*)(i*attrSize_));
        glEnableVertexAttribArray(i);
    }
    
    // EBO
    if (!indices_) return;
    
    glGenBuffers(1, &EBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIdx_ * sizeof(unsigned int), indices_.get(), GL_STATIC_DRAW);
}

// SEPARATE arrays

void Model::GenArrayBuffer(const float attribArray[], int elemPerAttr, int numVerts)
{
    numVerts_ = numVerts;
    
    // VAO
    glBindVertexArray(VAO_);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs_.push_back(VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, elemPerAttr, attribArray, GL_STATIC_DRAW);
    int idx = VBOs_.size()-1;
    glVertexAttribPointer(idx, elemPerAttr, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(idx);

    glBindVertexArray(0);
}

void Model::GenElementBuffer(unsigned int indices[], int numIdx)
{
    numIdx_ = numIdx;
    
    // VAO
    glBindVertexArray(VAO_);
    
    glGenBuffers(1, &EBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIdx_ * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

// RENDER

void Model::Render()
{
    glBindVertexArray(VAO_);
    
    if (indices_) {
        glDrawElements(mode_, numIdx_, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(mode_, 0, numVerts_);
    }
    
    glBindVertexArray(0);
}

// DESTRUCTOR

Model::~Model()
{
    bool delVBO = vertices_.use_count() <= 1;
    bool delEBO = indices_.use_count() <= 1;
    if (delVBO) {
        glDeleteBuffers(1, &VBO_);
    }
    if (delEBO) {
        glDeleteBuffers(1, &EBO_);
    }
    if (delVBO && delEBO) {
        glDeleteVertexArrays(1, &VAO_);
    }
};
