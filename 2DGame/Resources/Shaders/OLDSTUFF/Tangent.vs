#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tanget;

out Vertex{
vec3 worldPos; 
vec2 coord; 
mat3 tbnMatrix;
} vertex;






uniform mat4 MVP;
uniform mat4 model;

void main(){

vertex.worldPos = vec3(model * vec4(position, 1));
vertex.coord = texCoord;

gl_Position = MVP * vec4(position, 1);


vec3 n = normalize((model * vec4(normal, 0.0)).xyz);
vec3 t = normalize((model * vec4(tanget, 0.0)).xyz);
        
t = normalize(t - (dot(t,n)) * n);

vec3 biTanget =cross(n, t);
        

vertex.tbnMatrix = mat3(t, biTanget, n);



}

