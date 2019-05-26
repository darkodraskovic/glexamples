#include "Cube.h"

using namespace glm;

Cube::Cube(const glm::vec3& diffuseColor) :
    diffuseColor_(diffuseColor)
{
    
};

void Cube::GenerateModel()
{
    vec3 frontBL(-0.5f, -0.5f, 0.5f);
    vec3 frontTL(-0.5f, 0.5f, 0.5f);
    vec3 frontTR(0.5f, 0.5f, 0.5f);
    vec3 frontBR(0.5f, -0.5f, 0.5f);
    vec3 backBL = frontBL + zzz::BACK;
    vec3 backTL = frontTL + zzz::BACK;
    vec3 backTR = frontTR + zzz::BACK;
    vec3 backBR = frontBR + zzz::BACK;

    vec3 vertices[] = {
        // front
        frontBL, zzz::FORWARD, frontBR, zzz::FORWARD, frontTR, zzz::FORWARD, frontTL, zzz::FORWARD,
        // back
        backBR, zzz::BACK, backBL, zzz::BACK, backTL, zzz::BACK, backTR, zzz::BACK,
        // left
        backBL, zzz::LEFT, frontBL, zzz::LEFT, frontTL, zzz::LEFT, backTL, zzz::LEFT,
        // right
        frontBR, zzz::RIGHT, backBR, zzz::RIGHT, backTR, zzz::RIGHT, frontTR, zzz::RIGHT,
        // top
        frontTL, zzz::UP, frontTR, zzz::UP, backTR, zzz::UP, backTL, zzz::UP,          
        // bottom
        backBL, zzz::DOWN, backBR, zzz::DOWN, frontBR, zzz::DOWN, frontBL, zzz::DOWN,
    };
    int vLen = 24;
    int numAttrs = 2;

    unsigned int indices[] = {
        // front
        0, 1, 2,
        0, 2, 3,
        // back
        4, 5, 6,
        4, 6, 7,
        // left
        8, 9, 10,
        8, 10, 11,
        // left
        12, 13, 14,
        12, 14, 15,
        // top
        16, 17, 18,
        16, 18, 19,
        // bottom
        20, 21, 22,
        20, 22, 23,
    };
    int iLen = sizeof(indices)/sizeof(indices[0]);

    SetVertices(vertices, vLen, numAttrs);
    SetIndices(indices, iLen);
    Model::GenerateModel();
}
    
void Cube::Update(float deltaTime) {
    shader_->setVec3("uDiffuseColor", diffuseColor_);
    Rotate(deltaTime*100, zzz::ONE);
}
