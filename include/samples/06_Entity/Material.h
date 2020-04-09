#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "zzz.h"
#include "Shader.h"

using namespace glm;

class Material
{
public:
    Material();
    Material(std::shared_ptr<Shader> shader);
    virtual void Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

    std::shared_ptr<Shader> shader_;
};

#endif
