#ifndef CUBE_H
#define CUBE_H

#include "Model.h"

class Cube : public Model
{
public:
    Cube(const Shader& shader);
    virtual void Update(float time) override;
};

#endif
