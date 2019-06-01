#version 330 core

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTexCoords;

out vec3 FragPos;
out vec3 FragNorm;
out vec2 TexCoords;

void main()
{
    FragPos = mat3(uModel) * aPos;
    FragNorm = mat3(transpose(inverse(uModel))) * aNorm;
    TexCoords = aTexCoords.xy;

    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
