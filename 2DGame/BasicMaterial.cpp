#pragma once
#include "BasicMaterial.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "GameRenderLayer.h"
BasicMaterial::BasicMaterial(const string& filename) : Material(filename)
{
	shader = resourceManager->fetchShader("Resources/Shaders/DeferredWriter.glsl");
	
	//Yay, placeholders!
	setFloat("specularIntensity", 1.f);
	setFloat("specularPower", 500.f);

	if(!getTexture("normalMap")) setTexture("normalMap", resourceManager->fetchTexture("Resources/Textures/DefNormal.png"));

}

BasicMaterial::~BasicMaterial()
{
	resourceManager->freeShader(shader);
}

bool BasicMaterial::render(U32 renderType, GameObject* go)
{
	
	if (renderType == RenderLayerID<GameRenderLayer>::getID()) {
		
	
		shader->bind();
	
		
		
		shader->updateUniforms(this, go->getTransform());
		
		return true;
	}
	return false;
	
}
