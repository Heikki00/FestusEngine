#include "Input.h"

Input::Input()
{
	keys.reserve(20);
	mouseButtons.reserve(6);
}


bool Input::isKeyActive(SDL_Keycode k)
{
	for (auto& a : keys) {
		if (a.keysym.sym == k) {
			
			return true;
		}
	}
	return false;
}

bool Input::wasKeyPressed(SDL_Keycode k)
{
	auto p = this->getKeyEvent(k);

	return p && p->padding2;
}

bool Input::isMouseButtonActive(U8 mouseButton)
{
	for (auto& a : mouseButtons) {
		if (a.button == mouseButton) {
			
			return true;
		}
	}
	return false;
}

bool Input::wasMouseButtonPressed(U8 mouseButton)
{
	auto p = this->getMouseButtonEvent(mouseButton);

	return p && p->padding1;
}

Vector2 Input::getMouseLocation()
{
	return Vector2((F32)motionEvent.x, (F32)motionEvent.y);
}

Vector2 Input::getMouseMotion()
{
	return Vector2((F32)motionEvent.xrel, (F32)motionEvent.yrel);
}

void Input::updateMouseMotion(SDL_MouseMotionEvent e)
{
	motionEvent = e;
}

void Input::invalidateJustPressed()
{
	for (auto& a : keys) {
		a.padding2 = 0;
	}

	for (auto& a : mouseButtons) {
		a.padding1 = 0;
	}
}

void Input::setMousewheelChange(U32 change)
{
	mousewheelChange = change;
}

SDL_MouseMotionEvent& Input::getMouseMotionEvent()
{
	return motionEvent;
}

SDL_KeyboardEvent* Input::getKeyEvent(SDL_Keycode k)
{
	for (auto& a : keys) {
		if (a.keysym.sym == k) {
			return &a;
		}
	}
	return nullptr;
}

SDL_MouseButtonEvent* Input::getMouseButtonEvent(U8 mouseButton)
{
	for (auto& a : mouseButtons) {
		if (a.button == mouseButton) {
			return &a;
		}
	}
	return nullptr;
}

void Input::captureMouse(bool enabled)
{
	SDL_SetRelativeMouseMode(SDL_bool(enabled));
}

bool Input::isMouseCaptured()
{
	return SDL_GetRelativeMouseMode() == SDL_TRUE;
}

U32 Input::getMouseWheelChange()
{
	return mousewheelChange;
}

void Input::activateKey(const SDL_KeyboardEvent& e)
{
	keys.push_back(e);
	keys.at(keys.size() - 1).padding2 = 1;
}

void Input::deactivateKey(const SDL_KeyboardEvent& e)
{
	for (auto i = keys.begin(); i != keys.end(); ++i) {
		if (i->keysym.sym == e.keysym.sym) {
			keys.erase(i);
			return;
		}
	}
	
}

void Input::activateMouseButton(const SDL_MouseButtonEvent& e)
{
	mouseButtons.push_back(e);
	mouseButtons.at(mouseButtons.size() - 1).padding1 = 1;
}

void Input::deactivateMouseButton(const SDL_MouseButtonEvent& e)
{
	for (auto i = mouseButtons.begin(); i != mouseButtons.end(); ++i) {
		if (i->button == e.button){
			mouseButtons.erase(i);
			return;
		}
	}
}
