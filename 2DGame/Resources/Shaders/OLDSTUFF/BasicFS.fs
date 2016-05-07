#version 430

in vec2 pos2;
in vec2 coord0;

out vec4 color;

uniform sampler2D M_diffuse;

void main(){ 
       
         color = texture(M_diffuse, coord0); 
       
         //color = vec4(coord0, 0, 1);
      }  


