#version 330 core

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aVNorm;

out vec3 VNorm;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    mat3 mdl;
    mdl[0] = uModel[0].xyz; mdl[1] = uModel[1].xyz; mdl[2] = uModel[2].xyz;
    VNorm = mdl * aVNorm;
}
