#include "Model.h"

Model::Model()
{
}

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

void Model::SetVertices(float vertices[], int numVerts, int numAttrs, int attrSize)
{
    attrSize_ = attrSize;
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
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    // VBO
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    // data
    glBufferData(GL_ARRAY_BUFFER, numVerts_ * vertSize_, vertices_.get(), GL_STATIC_DRAW);
    // attrib pointers
    for (int i = 0; i < numAttrs_; ++i) {
        glVertexAttribPointer(
            i, attrSize_/sizeof(float),
            GL_FLOAT, GL_FALSE,
            vertSize_, (void*)(i*attrSize_));
        glEnableVertexAttribArray(i);
    }
    
    // EBO
    glGenBuffers(1, &EBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIdx_ * sizeof(unsigned int), indices_.get(), GL_STATIC_DRAW);
}

void Model::Copy(Model* model)
{
    // VBO
    VBO_ = model->VBO_;
    vertices_ = std::shared_ptr<float []>(model->vertices_);
    numVerts_ = model->numVerts_;
    numAttrs_ = model->numAttrs_;
    attrSize_ = model->attrSize_;
    vertSize_ = model->vertSize_;
    // EBO
    EBO_ = model->EBO_;
    indices_ = std::shared_ptr<unsigned int []>(model->indices_);
    numIdx_ = model->numIdx_;
    // VAO
    VAO_ = model->VAO_;
}

void Model::Render()
{
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, numIdx_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

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
