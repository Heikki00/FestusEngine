#pragma once
#include "GameRenderLayer.h"
#include "GameObject.h"
#include "BaseLight.h"
#include "DirectionalLight.h"


GameRenderLayer::GameRenderLayer()
{
	RenderLayerID<GameRenderLayer>::init(1);

	Texture* color = new Texture("gBufferC", nullptr, window->getWidth(), window->getHeight(), 1, GL_TEXTURE_2D, GL_RGBA, GL_RGBA8, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT);
	Texture* norm = new Texture("gBufferN", nullptr, window->getWidth(), window->getHeight(), 1, GL_TEXTURE_2D, GL_RGBA, GL_RGBA16F, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT);
	Texture* pos = new Texture("gBufferP", nullptr, window->getWidth(), window->getHeight(), 1, GL_TEXTURE_2D, GL_RGBA, GL_RGBA16F, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT);
	Texture* depth = new Texture("gBufferD", nullptr, window->getWidth(), window->getHeight(), 1, GL_TEXTURE_2D, GL_R, GL_R32F, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT);


	resourceManager->loadTexture(color);
	resourceManager->loadTexture(norm);
	resourceManager->loadTexture(pos);
	resourceManager->loadTexture(depth);

	setTexture("gBuffer_0", color);
	setTexture("gBuffer_1", norm);
	setTexture("gBuffer_2", pos);
	setTexture("gBuffer_3", depth);

	
	buffer = new FrameBuffer();
	buffer->attachTexture(color, GL_COLOR_ATTACHMENT0);

	buffer->attachTexture(norm, GL_COLOR_ATTACHMENT1);

	buffer->attachTexture(pos, GL_COLOR_ATTACHMENT2);

	buffer->attachTexture(depth, GL_COLOR_ATTACHMENT3);

	//buffer->attachRenderbuffer(GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT16, window->getWidth(), window->getHeight());

	shaders.push_back(resourceManager->fetchShader("Resources/Shaders/DeferredAmbient.glsl"));
	shaders.push_back(resourceManager->fetchShader("Resources/Shaders/DeferredDirectional.glsl"));
	shaders.push_back(resourceManager->fetchShader("Resources/Shaders/DeferredPoint.glsl"));
	//glClearColor(0.086, 0.4258, 0.8281, 1);
	glClearColor(0, 0, 0, 1);
}

GameRenderLayer::~GameRenderLayer() {

	delete buffer;

	for (Shader* s : shaders) resourceManager->freeShader(s);

}




void GameRenderLayer::render(GameObject* root)
{
	buffer->bindAsRenderTarget();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearDepth(-100.f);
	glDepthFunc(GL_LESS);


	root->renderAll(RenderLayerID<GameRenderLayer>::getID());
	
	window->bindAsRenderTarget();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	canvas.render(shaders.at(0));

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_ALWAYS);

	


	for (BaseLight* l : renderingEngine->getLights()) {
		if (!l->isEnabled()) continue;
		if (l->getType() == TypeID<DirectionalLight>::getType()) {
			renderingEngine->setUniformStruct("directionalLight", l);
			canvas.render(shaders.at(1));
		}

		else if (l->getType() == TypeID<PointLight>::getType()) {
			renderingEngine->setUniformStruct("pointLight", l);
			canvas.render(shaders.at(2));
		}



	}
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);



	

}

