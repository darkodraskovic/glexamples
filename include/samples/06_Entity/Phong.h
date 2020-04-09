#ifndef PHONG__H
#define PHONG__H

#include "Material.h"

using namespace glm;

class Phong : public Material
{
public:
    Phong(std::shared_ptr<Shader> shader);
    virtual void Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

    vec3 ambient_;
    vec3 diffuse_;
    vec3 specular_;
    
    float shininess_;
};

#endif
