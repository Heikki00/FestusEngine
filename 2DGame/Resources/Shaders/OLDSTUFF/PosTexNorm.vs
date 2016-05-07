#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 coord;
layout(location = 2) in vec3 norm;

out vec3 worldPos0;
out vec2 coord0;
out vec3 norm0;

uniform mat4 MVP;
uniform mat4 model;
void main(){

gl_Position = MVP * vec4(pos, 1);
coord0 = coord;
norm0 = norm;
worldPos0 = vec3(model * vec4(pos, 1));

}

