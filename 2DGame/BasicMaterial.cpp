#pragma once
#include "BasicMaterial.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "GameRenderLayer.h"
BasicMaterial::BasicMaterial(const string& filename, Shader* s) : Material(filename)
{
	shader = s;
	glDepthMask(GL_TRUE);


	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_CLAMP);
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
