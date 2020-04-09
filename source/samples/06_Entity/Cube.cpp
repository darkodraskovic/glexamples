#include "Cube.h"

using namespace glm;

Cube::Cube(const std::shared_ptr<Material>& material)
{
    material_ = material;

    vec3 frontBL(-0.5f, -0.5f, 0.5f);
    vec3 frontTL(-0.5f, 0.5f, 0.5f);
    vec3 frontTR(0.5f, 0.5f, 0.5f);
    vec3 frontBR(0.5f, -0.5f, 0.5f);
    vec3 backBL = frontBL + zzz::BACK;
    vec3 backTL = frontTL + zzz::BACK;
    vec3 backTR = frontTR + zzz::BACK;
    vec3 backBR = frontBR + zzz::BACK;

    int elemPerAttr = 3;
    int numVerts = 24;
    vec3 *positions = new vec3[numVerts] { frontBL, frontBR, frontTR, frontTL,
            // back
            backBR, backBL, backTL, backTR,
            // left
            backBL, frontBL, frontTL, backTL,
            // right
            frontBR, backBR, backTR, frontTR,
            // top
            frontTL, frontTR, backTR, backTL,
            // bottom
            backBL, backBR, frontBR, frontBL,
            };
    vec3 *normals = new vec3[numVerts] { zzz::FORWARD, zzz::FORWARD, zzz::FORWARD, zzz::FORWARD,
            // back
            zzz::BACK, zzz::BACK, zzz::BACK, zzz::BACK,
            // left
            zzz::LEFT, zzz::LEFT, zzz::LEFT, zzz::LEFT,
            // right
            zzz::RIGHT, zzz::RIGHT, zzz::RIGHT, zzz::RIGHT,
            // top
            zzz::UP, zzz::UP, zzz::UP, zzz::UP,
            // bottom
            zzz::DOWN, zzz::DOWN, zzz::DOWN, zzz::DOWN,
            };
    vec3 *texCoords = new vec3[numVerts]{ zzz::ZERO, zzz::RIGHT, zzz::ONE, zzz::UP,
            // back
            zzz::ZERO, zzz::RIGHT, zzz::ONE, zzz::UP,
            // left
            zzz::ZERO, zzz::RIGHT, zzz::ONE, zzz::UP,
            // right
            zzz::ZERO, zzz::RIGHT, zzz::ONE, zzz::UP,
            // top
            zzz::ZERO, zzz::RIGHT, zzz::ONE, zzz::UP,
            // bottom
            zzz::ZERO, zzz::RIGHT, zzz::ONE,zzz::UP,
            };
    mesh_->GenArrayBuffer((float*)positions, elemPerAttr, numVerts);
    mesh_->GenArrayBuffer((float*)normals, elemPerAttr, numVerts);
    mesh_->GenArrayBuffer((float*)texCoords, elemPerAttr, numVerts);

    int numIdx = 6 * 2 * 3; // num sides x num tris per side x num verts per tri
    unsigned int* indices = new unsigned int[numIdx]{ 0, 1, 2, 0, 2, 3,
            // back
            4, 5, 6, 4, 6, 7,
            // left
            8, 9, 10, 8, 10, 11,
            // right
            12, 13, 14, 12, 14, 15,
            // top
            16, 17, 18, 16, 18, 19,
            // bottom
            20, 21, 22, 20, 22, 23,
            };
    mesh_->GenElementBuffer(indices, numIdx);
}

void Cube::Update(float deltaTime) {
    Rotate(deltaTime*50, zzz::ONE);
}
