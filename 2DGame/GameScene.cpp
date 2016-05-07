#pragma once
#include "GameScene.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "FreeMove.h"
#include "DirectionalLight.h"
#include "GameRenderLayer.h"
#include "GUIRenderLayer.h"
#include "ImageData.h"
#include "BasicMaterial.h"


GameScene::GameScene()
{
	type = TypeID<GameScene>::getType();
}

void GameScene::init()
{
	root = new GameObject("root");

	gui->setActiveContext("GameScene");

	CEGUI::Window* w = gui->addWindow("TaharezLook/Button", "PlayButton", Vector4(0.3f, 0.1f, 0.4f, 0.2f));
	//w->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::SubscriberSlot(&MainMenu::startGame, this));
	w->setText("PLAY");
	GameObject* rend = new GameObject("Quad");
	
	Material* m = new BasicMaterial("Resources/Files/TestMat.mat", resourceManager->fetchShader("Resources/Shaders/TestShader.glsl"));

	m->setTexture("diffuse", resourceManager->fetchTexture("Resources/Textures/Grid.png"));


	rend->addComponent(new MeshRenderer(resourceManager->fetchMesh("Resources/Meshes/Square.obj", VertexType::P), m));

	GameObject* cam = new GameObject("Camera");

	cam->addComponent(new Camera(-1, 1, 1, -1, -1, 1));

	renderingEngine->setCamera((Camera*)cam->getComponentOfType(TypeID<Camera>::getType()));


	root->addChild(cam);
	root->addChild(rend);


}

GameScene::~GameScene()
{
	delete root;
}

void GameScene::update()
{
	

	root->updateAll();


}

void GameScene::render()
{

	renderingEngine->render(root);

}

void GameScene::activate()
{
	gui->setActiveContext("GameScene");
	input->captureMouse(true);
	renderingEngine->addLayer(new GameRenderLayer());
//	renderingEngine->disableGUI();
	
	renderingEngine->setCamera(static_cast<Camera*>(root->getChildByName("Camera")->getComponentByIndex(0)));

	static_cast<GUIRenderLayer*>(renderingEngine->getGUILayer())->setClear(false);

}

void GameScene::deactivate()
{
	renderingEngine->removeLayer(0);
} 

