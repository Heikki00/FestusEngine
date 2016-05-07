#pragma once
#include "SDL/SDL.h"


//Class for getting input from user to anywhere. Class stores everything as SDL_* events, wich can be accessed.
class Input {

public:

	Input();


	//Returns true if the key is active. SDL_Keycodes are SDLK_*
	bool isKeyActive(SDL_Keycode k);

	//Returns true if the key was pressed in this frame. SDL_Keycodes are SDLK_*
	bool wasKeyPressed(SDL_Keycode k);

	//Returns true if the mouse button is pressed
	bool isMouseButtonActive(U8 mouseButton);

	//Returns true if the mouse button was pressed in this frame. SDL_BUTTON_*
	bool wasMouseButtonPressed(U8 mouseButton);

	//Returns the location of the mouse in window
	Vector2 getMouseLocation();

	//Returns the movement mouse has had after last update
	Vector2 getMouseMotion();

	
	//Returns a reference to the latest mouse motion event
	SDL_MouseMotionEvent& getMouseMotionEvent();

	//Returns a pointer to the event of key k, and nullptr if the key has no event
	SDL_KeyboardEvent* getKeyEvent(SDL_Keycode k);

	//Returns a pointer to the event of button mouseButton, and nullptr if the button has no event
	SDL_MouseButtonEvent* getMouseButtonEvent(U8 mouseButton);

	//Sets the state of the mouse capture. Enabled == true, mouse gets captured
	void captureMouse(bool enabled);

	//Returns true if the mouse is captured
	bool isMouseCaptured();
	
	//Returns the mousewheel change. 1, 0 or -1 
	U32 getMouseWheelChange();

	//Adds the event to the list of current events
	void activateKey(const SDL_KeyboardEvent& e);

	//Removes the event from the list of current events
	void deactivateKey(const SDL_KeyboardEvent& e);

	//Adds the event to the list of current events
	void activateMouseButton(const SDL_MouseButtonEvent& e);

	//Removes the event from the list of current events
	void deactivateMouseButton(const SDL_MouseButtonEvent& e);

	//Sets the mouse motion event to e
	void updateMouseMotion(SDL_MouseMotionEvent e);

	//Invalidates the keys pressed in this frame
	void invalidateJustPressed();

	//Sets the mouse wheel change. Should be -1, 0 or 1
	void setMousewheelChange(U32 change);

private:
	std::vector<SDL_KeyboardEvent> keys;

	std::vector<SDL_MouseButtonEvent> mouseButtons;

	SDL_MouseMotionEvent motionEvent;
	
	U32 mousewheelChange;

};

