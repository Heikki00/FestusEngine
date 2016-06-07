#pragma once
#include "GameScene.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "FreeMove.h"
#include "DirectionalLight.h"
#include "GameRenderLayer.h"
#include "GUIRenderLayer.h"
#include "BasicMaterial.h"


GameScene::GameScene()
{
	type = TypeID<GameScene>::getType();
}

void GameScene::init()
{
	root = new GameObject("root");

	
	renderingEngine->setVector3("ambient", Vector3(0.1));

	GameObject* floor = new GameObject("Floor");
	

	Material* m = new BasicMaterial("Resources/Files/TestMat.mat");



	floor->addComponent(new MeshRenderer(resourceManager->fetchMesh("Resources/Meshes/Square.obj", VertexType::PTNT), m));

	floor->getTransform().rotate(Quaternion(Vector3(1, 0, 0), PI / 2));
	floor->getTransform().scale(5);

	GameObject* sun = new GameObject("sun");

	sun->addComponent(new DirectionalLight(Vector3(1), 1));
	sun->getTransform().rotate(Quaternion(Vector3(1,0,0), -PI / 4));

	GameObject* redLight = new GameObject("redL");

	redLight->addComponent(new PointLight(Vector3(1, 0.2, 0.2), 20.f, 0.3f));
	redLight->getTransform().setPosition(Vector3(0,0.1,0));

	GameObject* cam = new GameObject("Camera");

	cam->addComponent(new Camera(1.6, 800 / 600, 0.001, 1000.0));
	cam->addComponent(new FreeMove());


	root->addChild(cam);
	root->addChild(floor);
	root->addChild(sun);
	root->addChild(redLight);
}

GameScene::~GameScene()
{
	delete root;
}

void GameScene::update()
{
	root->getChildByName("redL")->getTransform().translate(Vector3(0, 0, 0.005));

	
	root->updateAll();

	


	if (input->isKeyActive(SDLK_p)) {
		root->getChildByName("sun")->getTransform().rotate(Quaternion(Vector3(1, 0, 0), 0.01));
	}
	else if (input->isKeyActive(SDLK_o)) {
		root->getChildByName("sun")->getTransform().rotate(Quaternion(Vector3(1, 0, 0), -0.01));
	}


	if (input->wasKeyPressed(SDLK_t)) {
		saveManager->save(root);
	}





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

