#version 430

in Vertex{
    vec2 coord;
} vertex;

uniform sampler2D M_diffuse;

out vec4 finalColor;

void main(){
        finalColor = texture(M_diffuse, vertex.coord);

}


