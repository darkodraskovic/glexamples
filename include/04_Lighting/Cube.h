#ifndef CUBE_H
#define CUBE_H

#include "Model.h"

class Cube : public Model
{
public:
    Cube(const Shader& shader, const glm::vec3& color);
    virtual void Update(float time) override;

    glm::vec3 diffuseColor_;
};

#endif
