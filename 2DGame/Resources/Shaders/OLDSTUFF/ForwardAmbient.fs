#version 430

in Vertex{
vec3 worldPos; 
vec2 coord; 
mat3 tbnMatrix;
} vertex;


out vec4 finalColor;

uniform vec3 RL_ambient;
uniform sampler2D M_diffuse;

void main(){

         finalColor = vec4(texture(M_diffuse, vertex.coord).xyz * RL_ambient, 1);   
             
    }