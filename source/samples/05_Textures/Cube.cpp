#include "Cube.h"

using namespace glm;

Cube::Cube() {};

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

    int vLen = 24;
    int numAttrs = 3;
    vec3 *vertices = new vec3[vLen * numAttrs]{
        // front
        frontBL, zzz::FORWARD, zzz::ZERO,
        frontBR, zzz::FORWARD, zzz::RIGHT,
        frontTR, zzz::FORWARD, zzz::ONE,
        frontTL, zzz::FORWARD, zzz::UP,   
        // back
        backBR, zzz::BACK, zzz::ZERO, 
        backBL, zzz::BACK, zzz::RIGHT,
        backTL, zzz::BACK, zzz::ONE,  
        backTR, zzz::BACK, zzz::UP,   
        // left
        backBL, zzz::LEFT,   zzz::ZERO, 
        frontBL, zzz::LEFT,  zzz::RIGHT,
        frontTL, zzz::LEFT,  zzz::ONE,  
        backTL, zzz::LEFT,   zzz::UP,   
        // right
        frontBR, zzz::RIGHT, zzz::ZERO, 
        backBR, zzz::RIGHT,  zzz::RIGHT,
        backTR, zzz::RIGHT,  zzz::ONE,  
        frontTR, zzz::RIGHT, zzz::UP,   
        // top
        frontTL, zzz::UP, zzz::ZERO, 
        frontTR, zzz::UP, zzz::RIGHT,
        backTR, zzz::UP,  zzz::ONE,  
        backTL, zzz::UP,  zzz::UP,           
        // bottom
        backBL, zzz::DOWN,   zzz::ZERO, 
        backBR, zzz::DOWN,   zzz::RIGHT,
        frontBR, zzz::DOWN,  zzz::ONE,  
        frontBL, zzz::DOWN,  zzz::UP,   
    };
    SetVertices(vertices, vLen, numAttrs);
    
    int iLen = 6 * 2 * 3; // num sides x num tris per side x num verts per tri
    // unsigned int* indices = new unsigned int[iLen]{
    unsigned int* indices = new unsigned int[iLen]{
        // front
        0, 1, 2,
        0, 2, 3,
        // back
        4, 5, 6,
        4, 6, 7,
        // left
        8, 9, 10,
        8, 10, 11,
        // right
        12, 13, 14,
        12, 14, 15,
        // top
        16, 17, 18,
        16, 18, 19,
        // bottom
        20, 21, 22,
        20, 22, 23,
    };
    SetIndices(indices, iLen);
    
    Model::GenerateModel();
}

void Cube::Update(float deltaTime) {    
    Rotate(deltaTime*50, zzz::ONE);
}
