#ifndef ZZZ_H
#define ZZZ_H

#include <glm/glm.hpp>
/* #include <glm/gtc/matrix_transform.hpp> */
/* #include <glm/gtc/type_ptr.hpp> */

using namespace glm;
// using namespace zzz;

namespace zzz
{
    const vec3 BLACK(0.0f, 0.0f, 0.0f);
    const vec3 WHITE(1.0f, 1.0f, 1.0f);
    const vec3 DARK_GRAY(0.2f, 0.2f, 0.2f);    
    const vec3 GRAY(0.5f, 0.5f, 0.5f);
    const vec3 LIGHT_GRAY(0.8f, 0.8f, 0.8f);    
    const vec3 RED(1.0f, 0.0f, 0.0f);
    const vec3 GREEN(0.0f, 1.0f, 0.0f);
    const vec3 BLUE(0.0f, 0.0f, 1.0f);
    const vec3 YELLOW(1.0f, 1.0f, 0.0f);
    const vec3 MAGENTA(1.0f, 0.0f, 1.0f);
    const vec3 CYAN(0.0f, 1.0f, 1.0f);

    const vec3 UP(0.0f, 1.0f, 0.0f);
    const vec3 DOWN(0.0f, -1.0f, 0.0f);
    const vec3 RIGHT(1.0f, 0.0f, 0.0f);
    const vec3 LEFT(-1.0f, 0.0f, 0.0f);
    const vec3 FORWARD(0.0f, 0.0f, 1.0f);
    const vec3 BACK(0.0f, 0.0f, -1.0f);
    const vec3 ZERO(0.0f, 0.0f, 0.0f);
    const vec3 ONE(1.0f, 1.0f, 1.0f);


    struct PhongMaterial
    {
    PhongMaterial() : ambient(DARK_GRAY), diffuse(WHITE), specular(GRAY), shininess(32) {}
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    
        float shininess;
    };

    struct Light
    {
    Light() : position(UP), ambient(DARK_GRAY), diffuse(GRAY), specular(WHITE) {}
        vec3 position;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;    
    };
}

#endif
