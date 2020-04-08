#ifndef CUBE_H
#define CUBE_H

#include "Model.h"
#include "zzz.h"

using namespace zzz;

struct PhongMaterial
{
    PhongMaterial() : ambient(DARK_GRAY), diffuse(WHITE), specular(GRAY), shininess(32) {}
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float shininess;
};

class Cube : public Model
{
public:
    Cube();
    virtual void GenerateModel() override;
    virtual void Update(float time) override;

    PhongMaterial* material_;
};

#endif
