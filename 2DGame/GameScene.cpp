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


	GameObject* ship = new GameObject("Ship");
	
	Material* m = new BasicMaterial("Resources/Files/TestMat.mat", resourceManager->fetchShader("Resources/Shaders/Basic2D.glsl"));

	m->setTexture("diffuse", resourceManager->fetchTexture("Resources/Textures/Grid.png"));


	ship->addComponent(new MeshRenderer(resourceManager->fetchMesh("Resources/Meshes/Ship.obj", VertexType::PT), m));

	GameObject* cam = new GameObject("Camera");

	cam->addComponent(new Camera(1.6, 800 / 600, 0.001, 1000.0));
	cam->addComponent(new FreeMove());

	renderingEngine->setCamera((Camera*)cam->getComponentOfType(TypeID<Camera>::getType()));


	root->addChild(cam);
	root->addChild(ship);

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

