#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "zzz.h"
#include "Shader.h"

using namespace glm;

namespace material
{
    struct Phong
    {
        Phong() : ambient(zzz::DARK_GRAY), diffuse(zzz::WHITE), specular(zzz::GRAY), shininess(32.0f) {}
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    
        float shininess;
    };

    struct PhongMap
    {
    PhongMap() : diffuse(0), specular(0), emissive(0), shininess(32.0f) {}
        unsigned int diffuse;
        unsigned int specular;
        unsigned int emissive;
    
        float shininess;
    };
}

using namespace material;

class Material
{
public:
    Material();
    Material(Shader* shader);
    Material(Shader* shader, const std::string& type);
    virtual void Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

    Shader* shader_;
    Phong* phong_ { nullptr };
    PhongMap* phongMap_ { nullptr };
};

#endif
