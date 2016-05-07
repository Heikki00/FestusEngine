#pragma once
#include "GUIRenderLayer.h"


GUIRenderLayer::GUIRenderLayer(bool clear)
{
	RenderLayerID<GUIRenderLayer>::init(1);
	this->clear = clear;
}

GUIRenderLayer::~GUIRenderLayer()
{
	
}

void GUIRenderLayer::render(GameObject* root)
{
	
	if (clear) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthFunc(GL_ALWAYS);

	gui->render();


	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
	



}

bool GUIRenderLayer::shouldClear()
{
	return clear;
}

void GUIRenderLayer::setClear(bool clear)
{
	this->clear = clear;
}
