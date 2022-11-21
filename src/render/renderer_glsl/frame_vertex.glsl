#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aTexCoord;

//out vec4 ourColor;
out vec4 pointColor;
out vec2 TexCoord;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    //ourColor = vec4(aColor, 1.0);
    pointColor = vec4(aColor, aTexCoord.z);
    TexCoord = aTexCoord.xy;
}