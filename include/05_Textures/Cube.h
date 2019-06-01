#ifndef CUBE_H
#define CUBE_H

#include "Model.h"
#include "zzz.h"

class Cube : public Model
{
public:
    Cube();
    virtual void GenerateModel() override;
    virtual void Update(float time) override;
};

#endif
