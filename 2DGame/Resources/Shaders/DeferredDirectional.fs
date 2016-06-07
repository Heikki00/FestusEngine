#version 430

#include "Lighting.glh"

in vec2 texCoord;

out vec4 finalColor;

uniform DirectionalLight R_directionalLight;

uniform sampler2D RL_gBuffer_0;
uniform sampler2D RL_gBuffer_1;
uniform sampler2D RL_gBuffer_2;
uniform sampler2D RL_gBuffer_3;

uniform vec3 C_eyePos;




void main(){
gl_FragDepth = texture(RL_gBuffer_3, texCoord).r;




vec4 normalColor = texture(RL_gBuffer_1, texCoord);
vec4 posColor = texture(RL_gBuffer_2, texCoord);





    vec3 lightAmt = calcDirectionalLight(R_directionalLight, normalColor.xzy, posColor.xyz , C_eyePos,  normalColor.w, posColor.w);

   //vec3    lightAmt = dot(-R_directionalLight.direction, normalColor.xyz) * R_directionalLight.base.color * R_directionalLight.base.intensity;

    


    

finalColor =  texture(RL_gBuffer_0, texCoord)* vec4(lightAmt, 1);
    
      //  finalColor = ;
  



}








