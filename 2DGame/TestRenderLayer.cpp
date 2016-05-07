#pragma once
#include "TestRenderLayer.h"
#include "GameObject.h"

TestRenderLayer::TestRenderLayer()
{
	RenderLayerID<TestRenderLayer>::init(1);
}

void TestRenderLayer::render(GameObject* root)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	root->renderAll(TypeID<TestRenderLayer>::getType());



}
