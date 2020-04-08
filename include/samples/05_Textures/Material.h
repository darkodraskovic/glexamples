#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "zzz.h"
#include "Shader.h"

using namespace glm;

namespace MaterialDefinitions
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

using namespace MaterialDefinitions;

class Material
{
public:
    Material();
    Material(std::shared_ptr<Shader> shader);
    Material(std::shared_ptr<Shader>, const std::string& type);
    virtual void Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

    std::shared_ptr<Shader> shader_;
    std::unique_ptr<Phong> phong_;
    std::unique_ptr<PhongMap> phongMap_;
};

#endif
