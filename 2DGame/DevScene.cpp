#include "DevScene.h"
#include "GameRenderLayer.h"
#include "GUIRenderLayer.h"
#include "FreeMove.h"



DevScene::DevScene()
{
	type = TypeID<DevScene>::getType();
}

DevScene::~DevScene()
{
	delete root;
}

void DevScene::init()
{
	root = new GameObject("ROOT");

}

void DevScene::update()
{




	root->updateAll();

	
}

void DevScene::render()
{
	renderingEngine->render(root);
}

void DevScene::activate()
{
	gui->setActiveContext("DevScene");
	input->captureMouse(false);
	renderingEngine->addLayer(new GameRenderLayer());

	renderingEngine->setCamera(static_cast<Camera*>(root->getChildByName("Camera")->getComponentByIndex(0)));
	renderingEngine->disableGUI();
}

void DevScene::deactivate()
{
	renderingEngine->removeLayer(0);
	renderingEngine->enableGUI();
}
