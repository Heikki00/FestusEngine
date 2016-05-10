#pragma once
#include "GameRenderLayer.h"
#include "GameObject.h"
#include "BaseLight.h"
#include "DirectionalLight.h"


GameRenderLayer::GameRenderLayer()
{
	RenderLayerID<GameRenderLayer>::init(1);

}

void GameRenderLayer::render(GameObject* root)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearDepth(-100.f);
	glDepthFunc(GL_LESS);


	root->renderAll(RenderLayerID<GameRenderLayer>::getID());
	

	//glEnable(GL_BLEND);
	//glDepthMask(GL_FALSE);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//glDepthFunc(GL_GREATER);


	



	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_GREATER);
	//glDisable(GL_BLEND);

	//glEnable(GL_BLEND);
	//glDepthMask(GL_FALSE);
	//glBlendFunc(GL_ONE, GL_ONE);
	//glDepthFunc(GL_EQUAL);

	////root->renderAll(RenderLayerID<ForwardRenderLayer>::getID() + 2);

	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_LESS);
	//glDisable(GL_BLEND);
}

