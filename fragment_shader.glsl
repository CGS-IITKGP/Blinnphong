#version 330 core
out vec4 FragColor;
in vec3 outColor;
in vec2 TexCoord;

/*uniform sampler2D ourTexture; // Texture sampler

void main()
{
    //FragColor = texture(ourTexture, TexCoord);
    FragColor = texture(ourTexture, TexCoord) * vec4(outColor, 1.0);  
}*/
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}