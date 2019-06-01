#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
};

uniform Material uMaterial;
uniform Light uLight;
uniform vec3 uViewPos;

in vec3 FragPos;
in vec3 FragNorm;
in vec2 TexCoords;

out vec4 FragCol;

void main()
{
    // ambient
    vec3 ambient = uLight.ambient * texture(uMaterial.diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(FragNorm);
    vec3 lightDir = normalize(uLight.position - FragPos);
    float intensity = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uLight.diffuse * (intensity * texture(uMaterial.diffuse, TexCoords).rgb);

    // specular
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = uLight.specular * (spec * texture(uMaterial.specular, TexCoords).rgb);

    // emissive
    vec3 emissive = texture(uMaterial.emissive, TexCoords).rgb;
    
    vec3 result = ambient + diffuse + specular + emissive;
    // vec3 result = ambient + diffuse + emissive;
    FragCol = vec4(result, 1.0);
}
