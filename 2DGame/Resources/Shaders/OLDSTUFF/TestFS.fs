

#version 430

#include "Lighting.glh"

in Vertex{
vec3 worldPos; 
vec2 coord; 
mat3 tbnMatrix;
} vertex;


in mat3 tbnMatrix;
out vec4 color;

uniform sampler2D M_diffuse;
uniform sampler2D M_normal;


uniform DirectionalLight RL_activeLight;

uniform vec3 eyepos;

void main(){ 
   
//vec3 n = normalize(vertex.tbnMatrix * vec3(0,1,0))); 



 //color = vec4(texture(M_diffuse, vertex.coord).xyz * calcDirectionalLight(RL_activeLight, n, vertex.worldPos, eyepos, 10.f, 200.f), 1);

        color = vec4(0.0,0.0,0.0, 1.0);


        }  


