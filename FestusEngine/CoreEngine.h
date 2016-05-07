#pragma once



class FileManager;
class ResourceManager;
class Window;
class Game;

//Class that inits the whole engine and contains the main loop.
class CoreEngine {
public:

	//Assigns values to all of the global pointers, creates the window, inits everything needed
	void init(U32 width, U32 height, const string& title, Game* game);



	//Frees all the resources of this engine
	void free();

	//Exits the main loop next frame;
	void stop();

	//Starts the main loop
	void run();



private:

	
	bool isClosed;

};