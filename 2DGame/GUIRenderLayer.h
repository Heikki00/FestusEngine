#pragma once
#include "RenderLayer.h"



class GUIRenderLayer : public RenderLayer {

public:
	GUIRenderLayer(bool clear);

	~GUIRenderLayer();


	virtual void render(GameObject* root) override;

	bool shouldClear();

	void setClear(bool clear);

private:
	bool clear;
};


