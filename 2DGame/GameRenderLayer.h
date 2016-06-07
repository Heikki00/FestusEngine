#pragma once
#include "RenderLayer.h"
#include "Canvas.h"


class GameRenderLayer : public RenderLayer {

public:
	GameRenderLayer();

	~GameRenderLayer();



	virtual void render(GameObject* root) override;
private:
	FrameBuffer* buffer;
	Canvas canvas;
	std::vector<Shader*> shaders;
};


