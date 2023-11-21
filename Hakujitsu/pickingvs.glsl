#version 330 core
layout (location = 0) in vec3 aPos;



out vec4 F_ColorID;

uniform mat4 CamMatrix;
uniform mat4 model;

uniform vec4 aColor;


void main()
{
    gl_Position = CamMatrix*model*vec4(aPos, 1.0f);
    F_ColorID = aColor;
}