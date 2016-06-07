#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 textureCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tanget;

uniform mat4 MVP;
uniform mat4 model;

out vec2 texCoord;
out vec3 worldPos;
out mat3 tbnMatrix;

void main(){

    gl_Position = MVP * vec4(position, 1);
    
    texCoord = textureCoord.xy;

    worldPos = (model * vec4(position, 1)).xyz;
    
    vec3 n = normalize((model * vec4(normal, 0.0)).xyz);
    vec3 t = normalize((model * vec4(tanget, 0.0)).xyz);
    
    t = normalize(t - (dot(t,n)) * n);
    
    
    vec3 biTanget = (cross(t,n));
    
    tbnMatrix = mat3(t,biTanget, n);
    
    
    
    
}