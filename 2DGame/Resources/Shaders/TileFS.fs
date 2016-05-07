#version 430




in Vertex{
    vec2 pos;
    vec2 coord;
} vertex;


uniform vec3 M_tileColor;

out vec4 finalColor;

void main(){


 finalColor = vec4(M_tileColor, 1.f);




}


