#ifndef CUBE_H
#define CUBE_H

#include "Model.h"
#include "zzz.h"

class Cube : public Model
{
public:
    Cube(const glm::vec3& diffuseColor = zzz::WHITE);
    virtual void GenerateModel() override;
    virtual void Update(float time) override;

    glm::vec3 diffuseColor_;
};

#endif
