#ifndef ZZZ_H
#define ZZZ_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

namespace zzz
{
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
    const vec3 ONE(1.0f, 1.0f, 1.0f);
}

#endif
