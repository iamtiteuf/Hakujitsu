#version 330 core
out vec4 FragColor;  
in vec3 Color;  

in vec2 TexCord;
uniform sampler2D tex0;
  
void main()
 { 
  //FragColor = texture(tex0, TexCord);
  FragColor = vec4(Color,1.0f);
 }