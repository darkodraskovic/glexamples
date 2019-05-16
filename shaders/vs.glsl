#version 330 core

uniform mat4 uTransform;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aVCol;
layout (location = 2) in vec2 aTexCoord;

out vec3 VCol;
out vec2 TexCoord;

void main()
{
    gl_Position = uTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    VCol = aVCol;
    TexCoord = aTexCoord;
}
