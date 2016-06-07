#include "DevScene.h"
#include "GameRenderLayer.h"
#include "GUIRenderLayer.h"
#include "FreeMove.h"
#include "MeshRenderer.h"



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
	
	root = saveManager->load("Resources/Files/DefaultSave.save");

	
}

void DevScene::update()
{

	if (input->isKeyActive(SDLK_p)) {
		root->getChildByName("sun")->getTransform().rotate(Quaternion(Vector3(1, 0, 0), 0.01));
	}
	else if (input->isKeyActive(SDLK_o)) {
		root->getChildByName("sun")->getTransform().rotate(Quaternion(Vector3(1, 0, 0), -0.01));
	}


	root->updateAll();

	
}

void DevScene::render()
{

	renderingEngine->render(root);
}

void DevScene::activate()
{

	gui->setActiveContext("DevScene");
	input->captureMouse(true);
	renderingEngine->addLayer(new GameRenderLayer());

	renderingEngine->setCamera(static_cast<Camera*>(root->getChildByName("Camera")->getComponentByIndex(0)));
	renderingEngine->disableGUI();

	static_cast<GUIRenderLayer*>(renderingEngine->getGUILayer())->setClear(false);
}

void DevScene::deactivate()
{

	
	renderingEngine->removeLayer(0);
	renderingEngine->enableGUI();
}
