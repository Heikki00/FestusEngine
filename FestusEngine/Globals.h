#pragma once

//File that has all the global pointers in it


class FileManager;
class ResourceManager;
class Window;
class RenderingEngine;
class Input;
class FestusTime;
class EventSystem;
class GUI;
class CoreEngine;
class SaveManager;

extern FileManager* fileManager;
extern ResourceManager* resourceManager;
extern Window* window;
extern RenderingEngine* renderingEngine;
extern Input* input;
extern FestusTime* ftime;
extern EventSystem* eventSystem;
extern GUI* gui;
extern CoreEngine* coreEngine;
extern Game* game;
extern SaveManager* saveManager;