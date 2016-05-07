#pragma once
#include "SDL/SDL.h"

//Window class. Inits OpenGL.
class Window
{
public:

	//Creates SDL window and OpenGL context
	Window(U32 width, U32 height, const std::string& title);
	~Window();

	inline SDL_Window* getWindow() { return window; }
	inline SDL_GLContext getContex() { return glContex; }

	//Returns true if window should close (for example, alt + f4)
	inline bool isClosed() { return _isClosed; }
	inline std::string getTitle() { return title; }
	inline int getWidth() { return width; }
	inline int getHeight() { return height; }


	//Swaps window's buffers (Double buffering)
	void swapBuffers();

	//Updates window events, like moving or input (if binded). Call every frame
	void updateEvents();

	//Sets the default buffer as the render target
	void bindAsRenderTarget();

private:
	char red_bits, green_bits, blue_bits, alpha_bits;
	bool _isClosed;
	std::string title;
	U32 width, height;


	SDL_Window* window;
	SDL_GLContext glContex;
};

