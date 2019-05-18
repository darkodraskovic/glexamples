#include "Model.h"

Model::Model(glm::vec3* vertices, int vLen, unsigned int* indices, int iLen, const Shader& shader) :
    shader_(shader), vertices_(vertices), vLen_(vLen), indices_(indices), iLen_(iLen)
{
    int vSize = sizeof(glm::vec3)*2;

    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vLen * vSize, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vSize, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vSize, (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iLen * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    id_ = glm::mat4(1.0f);
    rotation_ = glm::mat4(1.0f);
    scale_ = glm::mat4(1.0f);
    translation_ = glm::mat4(1.0f);
    transform_ = glm::mat4(1.0f);
};

void Model::Draw(const glm::mat4& uView, const glm::mat4& uProjection)
{
    shader_.use();
    
    shader_.setMat4("uModel", translation_* scale_ * rotation_);
    shader_.setMat4("uView", uView);
    shader_.setMat4("uProjection", uProjection);
    
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, iLen_, GL_UNSIGNED_INT, 0);
}

void Model::SetRotation(float angle, const glm::vec3& axis)
{
    rotation_ = glm::rotate(id_, glm::radians(angle), axis);
}

void Model::SetScale(const glm::vec3& scale)
{
    scale_ = glm::scale(id_, scale);
}

void Model::SetTranslation(const glm::vec3& translation)
{
    translation_ = glm::translate(id_, translation);
}
