#include "Cube.h"
#include "zzz.h"

using namespace glm;

Cube::Cube(const Shader& shader) : Model(shader) {
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
        frontBL, zzz::RED, frontBR, zzz::RED, frontTR, zzz::BLUE, frontTL, zzz::MAGENTA,
        // back
        backBR, zzz::RED, backBL, zzz::GREEN, backTL, zzz::BLUE, backTR, zzz::MAGENTA,
        // left
        backBL, zzz::RED, frontBL, zzz::GREEN, frontTL, zzz::BLUE, backTL, zzz::CYAN,
        // right
        frontBR, zzz::RED, backBR, zzz::GREEN, backTR, zzz::BLUE, frontTR, zzz::CYAN,
        // top
        frontTL, zzz::RED, frontTR, zzz::GREEN, backTR, zzz::BLUE, backTL, zzz::YELLOW,          
        // bottom
        backBL, zzz::RED, backBR, zzz::GREEN, frontBR, zzz::BLUE, frontBL, zzz::YELLOW,
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
    GenerateModel();

};
    
void Cube::Update(float deltaTime) {
    // Rotate(deltaTime*100, zzz::ONE);
}
