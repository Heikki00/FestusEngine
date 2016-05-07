
#include "Window.h"
#include <glew.h>
#include "Input.h"
Window::Window(U32 width, U32 height, const std::string& title) {
	assert(width != 0 || height != 0);

	//Init SDL
	if (!SDL_WasInit(SDL_INIT_EVERYTHING)) {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			Debug::log(ErrorType::CRITICAL_ERROR, "SDL_Init failed during window creation\n");
			return;
		}
	}

	//Set up window and OpenGL context
	red_bits = 8;
	blue_bits = 8;
	green_bits = 8;
	alpha_bits = 8;


	_isClosed = false;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, red_bits);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, green_bits);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, blue_bits);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, alpha_bits);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, red_bits + blue_bits + green_bits);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);


	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	glContex = SDL_GL_CreateContext(window);


	glewExperimental = GL_TRUE;

	//Init glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		Debug::log(ErrorType::CRITICAL_ERROR, "Failed to init GLEW: %s\n", glewGetErrorString(err));

	}

	this->width = width;
	this->height = height;

	Debug::log(ErrorType::LOG, "Successfully created window %s(%u, %u)\n", title.c_str(), width, height);
}

void Window::bindAsRenderTarget() {

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glViewport(0, 0, width, height);


}


Window::~Window() {
	Debug::log(ErrorType::LOG, "Destroying SDL and OpenGL context...\n");
	SDL_GL_DeleteContext(glContex);
	SDL_DestroyWindow(window);
	
}


void Window::swapBuffers() {
	SDL_GL_SwapWindow(window);
}


CEGUI::Key::Scan SDLKeyToCEGUIKey(SDL_Keycode key);
CEGUI::MouseButton SDLButtonToCEGUIButton(U8 button);


void Window::updateEvents() {
	SDL_Event e;

	bool mouseMotionEvent = false, mousewheelEvent = false;;

	input->invalidateJustPressed();


	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			
			_isClosed = true;
		}


		else if (e.type == SDL_KEYDOWN) {
			if (!input->isKeyActive(e.key.keysym.sym)) {
				input->activateKey(e.key);
				
			}

			gui->getActiveContext()->injectKeyDown(SDLKeyToCEGUIKey(e.key.keysym.sym));
		}

		else if (e.type == SDL_KEYUP) {
			if (input->isKeyActive(e.key.keysym.sym)) {
				input->deactivateKey(e.key);
				
			}
			gui->getActiveContext()->injectKeyUp(SDLKeyToCEGUIKey(e.key.keysym.sym));
		}

		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (!input->isMouseButtonActive(e.button.button)) {
				input->activateMouseButton(e.button);
			
			}
			gui->getActiveContext()->injectMouseButtonDown(SDLButtonToCEGUIButton(e.button.button));
		
		}

		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (input->isMouseButtonActive(e.button.button)) {
				input->deactivateMouseButton(e.button);

			}

			gui->getActiveContext()->injectMouseButtonUp(SDLButtonToCEGUIButton(e.button.button));
		}

		else if (e.type == SDL_MOUSEMOTION) {
			input->updateMouseMotion(e.motion);
			mouseMotionEvent = true;
			gui->getActiveContext()->injectMousePosition(e.motion.x, e.motion.y);

		}

		else if (e.type == SDL_MOUSEWHEEL) {
			input->setMousewheelChange(e.wheel.y);
			mousewheelEvent = true;
			gui->getActiveContext()->injectMouseWheelChange((F32)e.wheel.y);
		}


		else if (e.type == SDL_TEXTINPUT) {
		

			gui->getActiveContext()->injectChar((CEGUI::utf32)e.text.text[0]);
		}



	}//while


	if (!mouseMotionEvent) {
		SDL_MouseMotionEvent e = input->getMouseMotionEvent();

		e.xrel = e.yrel = 0;
		
		input->updateMouseMotion(e);

	}

	if (!mousewheelEvent) {
		input->setMousewheelChange(0);
	}



}


CEGUI::MouseButton SDLButtonToCEGUIButton(U8 button) {

	switch (button)
	{

	case SDL_BUTTON_LEFT: return CEGUI::MouseButton::LeftButton;
	case SDL_BUTTON_RIGHT: return CEGUI::MouseButton::RightButton;
	case SDL_BUTTON_MIDDLE: return CEGUI::MouseButton::MiddleButton;
	case SDL_BUTTON_X1: return CEGUI::MouseButton::X1Button;
	case SDL_BUTTON_X2: return CEGUI::MouseButton::X2Button;

	default:
		return CEGUI::MouseButton::NoButton;
	}

}

CEGUI::Key::Scan SDLKeyToCEGUIKey(SDL_Keycode key)
{
	using namespace CEGUI;
	switch (key)
	{
	case SDLK_BACKSPACE:    return Key::Backspace;
	case SDLK_TAB:          return Key::Tab;
	case SDLK_RETURN:       return Key::Return;
	case SDLK_PAUSE:        return Key::Pause;
	case SDLK_ESCAPE:       return Key::Escape;
	case SDLK_SPACE:        return Key::Space;
	case SDLK_COMMA:        return Key::Comma;
	case SDLK_MINUS:        return Key::Minus;
	case SDLK_PERIOD:       return Key::Period;
	case SDLK_SLASH:        return Key::Slash;
	case SDLK_0:            return Key::Zero;
	case SDLK_1:            return Key::One;
	case SDLK_2:            return Key::Two;
	case SDLK_3:            return Key::Three;
	case SDLK_4:            return Key::Four;
	case SDLK_5:            return Key::Five;
	case SDLK_6:            return Key::Six;
	case SDLK_7:            return Key::Seven;
	case SDLK_8:            return Key::Eight;
	case SDLK_9:            return Key::Nine;
	case SDLK_COLON:        return Key::Colon;
	case SDLK_SEMICOLON:    return Key::Semicolon;
	case SDLK_EQUALS:       return Key::Equals;
	case SDLK_LEFTBRACKET:  return Key::LeftBracket;
	case SDLK_BACKSLASH:    return Key::Backslash;
	case SDLK_RIGHTBRACKET: return Key::RightBracket;
	case SDLK_a:            return Key::A;
	case SDLK_b:            return Key::B;
	case SDLK_c:            return Key::C;
	case SDLK_d:            return Key::D;
	case SDLK_e:            return Key::E;
	case SDLK_f:            return Key::F;
	case SDLK_g:            return Key::G;
	case SDLK_h:            return Key::H;
	case SDLK_i:            return Key::I;
	case SDLK_j:            return Key::J;
	case SDLK_k:            return Key::K;
	case SDLK_l:            return Key::L;
	case SDLK_m:            return Key::M;
	case SDLK_n:            return Key::N;
	case SDLK_o:            return Key::O;
	case SDLK_p:            return Key::P;
	case SDLK_q:            return Key::Q;
	case SDLK_r:            return Key::R;
	case SDLK_s:            return Key::S;
	case SDLK_t:            return Key::T;
	case SDLK_u:            return Key::U;
	case SDLK_v:            return Key::V;
	case SDLK_w:            return Key::W;
	case SDLK_x:            return Key::X;
	case SDLK_y:            return Key::Y;
	case SDLK_z:            return Key::Z;
	case SDLK_DELETE:       return Key::Delete;
	case SDLK_KP_0:          return Key::Numpad0;
	case SDLK_KP_1:          return Key::Numpad1;
	case SDLK_KP_2:          return Key::Numpad2;
	case SDLK_KP_3:          return Key::Numpad3;
	case SDLK_KP_4:          return Key::Numpad4;
	case SDLK_KP_5:          return Key::Numpad5;
	case SDLK_KP_6:          return Key::Numpad6;
	case SDLK_KP_7:          return Key::Numpad7;
	case SDLK_KP_8:          return Key::Numpad8;
	case SDLK_KP_9:          return Key::Numpad9;
	case SDLK_KP_PERIOD:    return Key::Decimal;
	case SDLK_KP_DIVIDE:    return Key::Divide;
	case SDLK_KP_MULTIPLY:  return Key::Multiply;
	case SDLK_KP_MINUS:     return Key::Subtract;
	case SDLK_KP_PLUS:      return Key::Add;
	case SDLK_KP_ENTER:     return Key::NumpadEnter;
	case SDLK_KP_EQUALS:    return Key::NumpadEquals;
	case SDLK_UP:           return Key::ArrowUp;
	case SDLK_DOWN:         return Key::ArrowDown;
	case SDLK_RIGHT:        return Key::ArrowRight;
	case SDLK_LEFT:         return Key::ArrowLeft;
	case SDLK_INSERT:       return Key::Insert;
	case SDLK_HOME:         return Key::Home;
	case SDLK_END:          return Key::End;
	case SDLK_PAGEUP:       return Key::PageUp;
	case SDLK_PAGEDOWN:     return Key::PageDown;
	case SDLK_F1:           return Key::F1;
	case SDLK_F2:           return Key::F2;
	case SDLK_F3:           return Key::F3;
	case SDLK_F4:           return Key::F4;
	case SDLK_F5:           return Key::F5;
	case SDLK_F6:           return Key::F6;
	case SDLK_F7:           return Key::F7;
	case SDLK_F8:           return Key::F8;
	case SDLK_F9:           return Key::F9;
	case SDLK_F10:          return Key::F10;
	case SDLK_F11:          return Key::F11;
	case SDLK_F12:          return Key::F12;
	case SDLK_F13:          return Key::F13;
	case SDLK_F14:          return Key::F14;
	case SDLK_F15:          return Key::F15;
	case SDLK_NUMLOCKCLEAR: return Key::NumLock;
	case SDLK_SCROLLLOCK:   return Key::ScrollLock;
	case SDLK_RSHIFT:       return Key::RightShift;
	case SDLK_LSHIFT:       return Key::LeftShift;
	case SDLK_RCTRL:        return Key::RightControl;
	case SDLK_LCTRL:        return Key::LeftControl;
	case SDLK_RALT:         return Key::RightAlt;
	case SDLK_LALT:         return Key::LeftAlt;
	case SDLK_LGUI:       return Key::LeftWindows;
	case SDLK_RGUI:       return Key::RightWindows;
	case SDLK_SYSREQ:       return Key::SysRq;
	case SDLK_MENU:         return Key::AppMenu;
	case SDLK_POWER:        return Key::Power;
	default:                return Key::Unknown;
	}
	 
}




