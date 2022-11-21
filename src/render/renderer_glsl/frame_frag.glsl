#version 330 core
out vec4 FragColor;
in vec4 pointColor;
in vec2 TexCoord;
uniform vec4 ourColor;
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(pointColor);
}
