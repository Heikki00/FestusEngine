#version 430

#include "Lighting.glh"

in Vertex{
vec3 worldPos; 
vec2 coord; 
mat3 tbnMatrix;
} vertex;

uniform sampler2D M_diffuse;
uniform sampler2D M_normal;

uniform float M_specularIntensity;
uniform float M_specularPower;

uniform DirectionalLight RL_activeLight;
uniform vec3 eyepos;

out vec4 finalColor;

void main(){
        vec3 n = normalize(vertex.tbnMatrix * (255.0/128.0 * texture(M_normal, vertex.coord).xyz - 1)); 

        vec3 color = texture(M_diffuse, vertex.coord).xyz;  
        
        finalColor = vec4(color * calcDirectionalLight(RL_activeLight, n, vertex.worldPos, eyepos, 1.f, 500.f), 1);
}






