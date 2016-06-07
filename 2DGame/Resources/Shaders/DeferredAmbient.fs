#version 430

in vec2 texCoord;

uniform sampler2D RL_gBuffer_0;
uniform sampler2D RL_gBuffer_1;
uniform sampler2D RL_gBuffer_2;
uniform sampler2D RL_gBuffer_3;
uniform vec3 R_ambient;

out vec4 finalColor;

void main(){
    gl_FragDepth  = texture(RL_gBuffer_3, texCoord).r;

    finalColor = texture( RL_gBuffer_0, texCoord) * vec4( R_ambient, 1);
    //finalColor = vec4(1,1,0, 1);

}