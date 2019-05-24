#version 330 core

uniform vec3 uDiffuseColor;
uniform vec3 uAmbientColor;
uniform vec3 uLightColor;
uniform vec3 uLightDirection;

in vec3 VNorm;

out vec4 FragColor;

void main()
{
    float lightIntensity = dot(uLightDirection, VNorm);
    lightIntensity = clamp(lightIntensity, 0.2, 1);
    // FragColor = vec4(uDiffuseColor * lightIntensity + uAmbientColor, 1.0);
    FragColor = vec4(uDiffuseColor * lightIntensity, 1.0);
}
