#version 330 core
layout(location = 0) out vec4  FragColor;
in vec4 F_ColorID; 


void main() 
{
   FragColor =  vec4(F_ColorID);
}
