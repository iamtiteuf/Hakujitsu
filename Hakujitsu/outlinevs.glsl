#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 model;
uniform mat4 CamMatrix;

uniform vec3 scale = vec3(1.05,1.05,1.05);

void main()
{
mat4 scaleMatrix = mat4(
        vec4(scale.x, 0.0, 0.0, 0.0),
        vec4(0.0, scale.y, 0.0, 0.0),
        vec4(0.0, 0.0, scale.z, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
         );  
    gl_Position = CamMatrix * model * scaleMatrix * vec4(aPos, 1.0f);
   
}