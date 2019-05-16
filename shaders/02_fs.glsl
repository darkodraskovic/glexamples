#version 330 core

in vec3 VCol;

out vec4 FragColor;

void main()
{
    FragColor = vec4(VCol, 1.0);
}
