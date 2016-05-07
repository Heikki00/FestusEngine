#pragma once
#include "TestGame.h"
#include "MainMenu.h"
#include "GUIRenderLayer.h"
#include "GameScene.h"
#include "DevScene.h"

void TestGame::init()
{
	physics = new Physics();
	
	gui->loadScheme("TaharezLook");
		gui->loadScheme("WindowsLook");
	
	renderingEngine->setGUILayer(new GUIRenderLayer(false));



	activeScene = new MainMenu();
	activeScene->init();
	scenes["MainMenu"] = activeScene;
	GameScene* gscene = new GameScene();
	gscene->init();
	scenes["GameScene"] = gscene;

	DevScene* dscene = new DevScene();
	dscene->init();
	scenes["DevScene"] = dscene;


	activeScene->activate();
}


TestGame::~TestGame()
{
	delete physics;
	for (auto a : scenes) {
		delete a.second;
	}

}

void TestGame::update()
{
	activeScene->update();

	


}

void TestGame::render()
{
	activeScene->render();
}
