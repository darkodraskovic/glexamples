#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>

#include "Model.h"
#include "Shader.h"
#include "zzz.h"

using namespace glm;

class Cube : public Model
{
public:
    Cube(const Shader& shader);
    
    virtual void Update(float time) override;
};

#endif
