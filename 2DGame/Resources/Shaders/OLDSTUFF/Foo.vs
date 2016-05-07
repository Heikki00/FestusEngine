#version 430

in vec3 position;

uniform mat4 MVP;

uniform float f1;



void main(){
        gl_Position = MVP * vec4(position, 1 + f1);
}

