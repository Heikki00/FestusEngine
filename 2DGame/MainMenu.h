#pragma once
#include "Scene.h"




class MainMenu : public Scene {
public:

	MainMenu();

	~MainMenu();

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;


	bool exitGame(const CEGUI::EventArgs& e);

	bool startGame(const CEGUI::EventArgs& e);

	bool devMode(const CEGUI::EventArgs& e);

	bool isGameStarted();

	virtual void activate() override;

private:

	bool gameStarted;

};