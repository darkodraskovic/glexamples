#ifndef CUBE_H
#define CUBE_H

#include "Material.h"
#include "Entity.h"
#include "zzz.h"

class Cube : public Entity
{
public:
    Cube(std::shared_ptr<Material>& material);
    virtual void Update(float time) override;
};

#endif
