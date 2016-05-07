#version 430



out vec4 color;

uniform float colorMult;



struct AlphaInfo{
float base;
float mul;

};

struct ColorInfo{

float r;

float g;

float b;

AlphaInfo a;       

};

uniform ColorInfo colInf;


void main(){
        color = vec4(colInf.r, colInf.g, colInf.b, colInf.a.base * colInf.a.mul) * colorMult;
}

