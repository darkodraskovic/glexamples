#version 330 core

uniform vec4 uColor;
uniform sampler2D texture0;
uniform sampler2D texture1;

in vec3 VCol;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    // FragColor = uColor;
    // FragColor = vec4(VCol, 1.0);
    // FragColor = texture(texture0, TexCoord);
    FragColor = texture(texture1, TexCoord);
    // FragColor = texture(texture1, vec2(1-TexCoord.x, TexCoord.y));
    // FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);
    // FragColor = mix(texture(texture0, TexCoord),
    //                 texture(texture1, TexCoord), 0.2) * vec4(VCol, 1.0);
}
