#include "Model.h"

Model::Model()
{
};

void Model::SetVertices(glm::vec3* vertices, int numVerts, int numAttrs)
{
    attrSize_ = sizeof(glm::vec3);
    SetVertices_(vertices, numVerts, numAttrs);
};

void Model::SetVertices(glm::vec4* vertices, int numVerts, int numAttrs)
{
    attrSize_ = sizeof(glm::vec4);
    SetVertices_(vertices, numVerts, numAttrs);
};

void Model::SetVertices(const void* vertices, int numVerts, int numAttrs, int attrSize)
{
    attrSize_ = attrSize;
    SetVertices_(vertices, numVerts, numAttrs);
}

void Model::SetVertices_(const void* vertices, int numVerts, int numAttrs)
{
    vertices_ = vertices;
    numVerts_ = numVerts;
    numAttrs_ = numAttrs;
    vertSize_ = numAttrs_ * attrSize_;    
}

void Model::SetIndices(unsigned int* indices, int numIdx)
{
    indices_ = indices;
    numIdx_ = numIdx;
};

void Model::GenerateModel()
{
    // VAO
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    // VBO
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    // data
    glBufferData(GL_ARRAY_BUFFER, numVerts_ * vertSize_, vertices_, GL_STATIC_DRAW);
    // attrib pointers
    for (int i = 0; i < numAttrs_; ++i) {
        glVertexAttribPointer(i, attrSize_/sizeof(float), GL_FLOAT, GL_FALSE, vertSize_, (void*)(i*attrSize_));
        glEnableVertexAttribArray(i);
    }
    
    // EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIdx_ * sizeof(unsigned int), indices_, GL_STATIC_DRAW);

    // Transform
    InitTransform_();
}

void Model::InitTransform_()
{
    id_ = glm::mat4(1.0f);
    rotation_ = glm::mat4(1.0f);
    scale_ = glm::mat4(1.0f);
    translation_ = glm::mat4(1.0f);
    transform_ = glm::mat4(1.0f);
};

void Model::Copy(Model* model)
{
    // VBO
    vertices_ = model->vertices_;
    numVerts_ = model->numVerts_;
    numAttrs_ = model->numAttrs_;
    attrSize_ = model->attrSize_;
    vertSize_ = model->vertSize_;
    // EBO
    indices_ = model->indices_;
    numIdx_ = model->numIdx_;
    // VAO
    VAO_ = model->VAO_;
    
    // Material
    material_ = model->material_;

    // Transform
    InitTransform_();
};

void Model::Render(float deltaTime, const glm::mat4& uView, const glm::mat4& uProjection)
{
    material_->Update(deltaTime, translation_* rotation_ * scale_, uView, uProjection);

    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, numIdx_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Model::SetRotation(float angle, const glm::vec3& axis)
{
    rotation_ = glm::rotate(id_, glm::radians(angle), axis);
}

void Model::Rotate(float angle, const glm::vec3& axis)
{
    rotation_ = glm::rotate(rotation_, glm::radians(angle), axis);
}

void Model::SetScale(const glm::vec3& scale)
{
    scale_ = glm::scale(id_, scale);
}

void Model::SetScale(float scale)
{
    scale_ = glm::scale(id_, glm::vec3(scale));
}

void Model::Scale(const glm::vec3& scale)
{
    scale_ = glm::scale(scale_, scale);
}

void Model::Scale(float scale)
{
    scale_ = glm::scale(scale_, glm::vec3(scale));
}

void Model::SetTranslation(const glm::vec3& translation)
{
    translation_ = glm::translate(id_, translation);
}

void Model::Translate(const glm::vec3& translation)
{
    translation_ = glm::translate(translation_, translation);
}

void Model::Update(float deltaTime)
{

};

Model::~Model()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
};
