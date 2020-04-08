#version 330 core

uniform mat4 uTransform;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = uTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
