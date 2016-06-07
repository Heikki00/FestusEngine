#pragma once
#include "Scene.h"

//Interface that represents the game. Game contains scenes, and game controls, which of these scenes to update and render
class Game {
public:

	virtual ~Game() = default;

	//Inits the game, called in CoreEngine::init()
	virtual void init() = 0;

	//Updates the game, called every frame. Meant to call one scenes update method
	virtual void update() = 0;

	//Renders the game, called every frame. Meant to call one scenes update method
	virtual void render() = 0;

	//Switches the scene, calls Scene::acticate and Scene::deactivate
	void switchScene(const string& scene) {
		activeScene->deactivate();
		activeScene = scenes[scene];
		activeScene->activate();
	}
	//Returns the active scene
	
	Scene* getActiveScene() {
		return activeScene;
	}

protected:
	std::map<string, Scene*> scenes;
	Scene* activeScene;


};







