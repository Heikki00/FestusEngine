#pragma once
#include "RenderLayer.h"



class GameRenderLayer : public RenderLayer {

public:
	GameRenderLayer();




	virtual void render(GameObject* root) override;

};


