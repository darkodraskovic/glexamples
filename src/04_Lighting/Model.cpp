#include "Model.h"

Model::Model()
{
};

void Model::SetVertices(glm::vec3* vertices, int vLen, int numAttrs)
{
    vertices3_ = vertices;
    vLen_ = vLen;
    numAttrs_ = numAttrs;
    vAttrSize_ = sizeof(glm::vec3);
    vSize_ = numAttrs_ * vAttrSize_;
};

void Model::SetVertices(glm::vec4* vertices, int vLen, int numAttrs)
{
    vertices4_ = vertices;
    vLen_ = vLen;
    numAttrs_ = numAttrs;
    vAttrSize_ = sizeof(glm::vec3);
    vSize_ = numAttrs_ * vAttrSize_;    
};

void Model::SetIndices(unsigned int* indices, int iLen)
{
    indices_ = indices;
    iLen_ = iLen;
};

void Model::GenerateModel()
{
    // VAO
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    if (vAttrSize_ == sizeof(glm::vec3)) {
        glBufferData(GL_ARRAY_BUFFER, vLen_ * vSize_, vertices3_, GL_STATIC_DRAW);
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, vLen_ * vSize_, vertices4_, GL_STATIC_DRAW);
    }
    
    for (int i = 0; i < numAttrs_; ++i)
    {
        glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, vSize_, (void*)(i*vAttrSize_));
        glEnableVertexAttribArray(i);
    }
    
    // EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iLen_ * sizeof(unsigned int), indices_, GL_STATIC_DRAW);

    // Transform
    InitTransform();
}

void Model::InitTransform()
{
    id_ = glm::mat4(1.0f);
    rotation_ = glm::mat4(1.0f);
    scale_ = glm::mat4(1.0f);
    translation_ = glm::mat4(1.0f);
    transform_ = glm::mat4(1.0f);
};

Model* Model::Clone(Model* model)
{
    // VBO, EBO, VAO
    if (model->vertices3_) {
        SetVertices(model->vertices3_, model->vLen_, model->numAttrs_);
    } else {
        SetVertices(model->vertices4_, model->vLen_, model->numAttrs_);
    }
    SetIndices(model->indices_, model->iLen_);
    VAO_ = model->VAO_;
    // Shader
    shader_ = model->shader_;
    // Transform
    InitTransform();
    
    return model;
};

void Model::Draw(const glm::mat4& uView, const glm::mat4& uProjection)
{
    shader_->use();

    shader_->setMat4("uModel", translation_* rotation_ * scale_);
    shader_->setMat4("uView", uView);
    shader_->setMat4("uProjection", uProjection);

    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, iLen_, GL_UNSIGNED_INT, 0);
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

void Model::Scale(const glm::vec3& scale)
{
    scale_ = glm::scale(scale_, scale);
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
