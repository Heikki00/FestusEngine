#include "CoreEngine.h"
#include "FileManager.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Game.h"
#include "RenderingEngine.h"
#include "Input.h"
#include "SaveManager.h"

void CoreEngine::init(U32 width, U32 height, const string& title, Game* gameParameter)
{
	
	Math::initMemory(1000, 500, 100, 100);
	Debug::init();

	isClosed = false;

	coreEngine = this;
	ftime = new FestusTime();
	input = new Input();
	window = new Window(width, height, title);
	fileManager = new FileManager();
	eventSystem = new EventSystem();
	resourceManager = new ResourceManager();
	renderingEngine = new RenderingEngine();
	gui = new GUI();
	saveManager = new SaveManager();
	game = gameParameter;
	game->init();

}

void CoreEngine::free()
{
	delete game;
	delete saveManager;
	delete gui;
	delete renderingEngine;
	delete resourceManager;
	delete eventSystem;
	delete fileManager;
	delete input;
	delete window;
	delete ftime;
	
	Math::freeMemory();

}

void CoreEngine::stop()
{
	isClosed = true;
}

void CoreEngine::run()
{
	
	F32 frameDone = 0.f;
	U32 frames = 0;

	while (!isClosed) {
		U32 start = ftime->getTime();

	
		window->updateEvents();
		

		if (window->isClosed()) {

			break;
		}

		eventSystem->update();


		game->update();

		game->render();
		
	
		U32 end = ftime->getTime();


		float delta = (end - start) / 1000.f;
		frames++;


		ftime->delta = delta;
		frameDone += delta;
		if (frameDone > 1.f) {
			
			std::cout << frames << std::endl;
			frameDone = 0.f;
			frames = 0;
		}
		
	
	
	}
}
