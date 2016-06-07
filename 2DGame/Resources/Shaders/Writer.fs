#version 430

in vec2 texCoord;
in vec3 worldPos;
in mat3 tbnMatrix;

uniform sampler2D diffuse;
uniform sampler2D normalMap;

uniform float specularIntensity;
uniform float specularPower;

layout (location = 0) out vec4 diffuseColor;
layout (location = 1) out vec4 normalColor;
layout (location = 2) out vec4 positionColor;
layout (location = 3) out float depthColor;


void main(){ 

vec3 n = normalize(tbnMatrix * (255.0/128.0 * texture(normalMap, texCoord).xyz - 1));
diffuseColor = texture(diffuse, texCoord);//1 is a placeholder for opacity
//diffuseColor = vec4(0.5,0,0.5,1);
normalColor = vec4(n, specularIntensity);
//normalColor = vec4(0,1,0, specularIntensity);

positionColor = vec4(worldPos, specularPower);

depthColor = gl_FragCoord.z;

}

