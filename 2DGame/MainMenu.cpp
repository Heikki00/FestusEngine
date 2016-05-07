#pragma once
#include "MainMenu.h"
#include "GUIRenderLayer.h"

MainMenu::MainMenu()
{
	type = TypeID<MainMenu>::getType();
}

MainMenu::~MainMenu()
{
	delete root;
}

void MainMenu::init()
{
	root = new GameObject("root");
	gui->setActiveContext("MainMenu");

	type = TypeID<MainMenu>::getType();

	CEGUI::Window* w = gui->addWindow("TaharezLook/Button", "PlayButton", Vector4(0.3f, 0.1f, 0.4f, 0.2f));
	w->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::SubscriberSlot(&MainMenu::startGame, this));
	w->setText("PLAY");
	
	

	w = gui->addWindow("TaharezLook/Button", "DevButton", Vector4(0.3f, 0.4f, 0.4f, 0.2f));
	w->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::SubscriberSlot(&MainMenu::devMode, this));
	w->setText("DEVMODE");

	w = gui->addWindow("TaharezLook/Button", "ExitButton", Vector4(0.3f, 0.7f, 0.4f, 0.2f));
	w->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::SubscriberSlot(&MainMenu::exitGame, this));
	w->setText("EXIT");

	static_cast<GUIRenderLayer*>(renderingEngine->getGUILayer())->setClear(true);

}

void MainMenu::update()
{
	root->updateAll();
}

void MainMenu::render()
{
	renderingEngine->render(root);
}

bool MainMenu::exitGame(const CEGUI::EventArgs& e)
{
	coreEngine->stop();

	return true;
}

bool MainMenu::startGame(const CEGUI::EventArgs& e)
{
	game->switchScene("GameScene");

	return true;
}

bool MainMenu::devMode(const CEGUI::EventArgs& e)
{
	game->switchScene("DevScene");

	return true;
}

bool MainMenu::isGameStarted()
{
	return gameStarted;
}

void MainMenu::activate()
{
	gui->setActiveContext("MainMenu");
	static_cast<GUIRenderLayer*>(renderingEngine->getGUILayer())->setClear(true);
}
