#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 texCoord;

uniform mat4 MVP;
uniform mat4 model;



out Vertex{
    vec2 coord;
} vertex;

void main(){
    gl_Position = MVP * vec4(position, 1);
    
   
    vertex.coord = texCoord.xy;
     
}
