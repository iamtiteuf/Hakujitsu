#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 Color;
out vec2 TexCord;

uniform mat4 CamMatrix;
uniform mat4 model;



void main()
{
    gl_Position = CamMatrix*model*vec4(aPos, 1.0f);
    Color = aColor;
    TexCord = aTex;
}