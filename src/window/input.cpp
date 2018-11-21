#include "input.h"
#include "../maths/kmath.h"
#include <cstring>

namespace kekule {

	unsigned char* Input::mKeyboard = new unsigned char[GLFW_KEY_LAST + 1];
	unsigned char* Input::mMouseBtn = new unsigned char[GLFW_MOUSE_BUTTON_LAST + 1];
	float Input::mMouseX(0.0f), Input::mMouseY(0.0f), Input::scrollX(0.0f), Input::scrollY(0.0f);
	std::list<Input::ReleasedKey> Input::mReleasedKeys;
	std::list<Input::ReleasedBtn> Input::mReleasedBtns;
	std::list<Input::PressedBtn>  Input::mPressedBtns;

	void Input::init() {
		memset (mKeyboard, INPUT_KEY_NOT_IN_ACTION, GLFW_KEY_LAST + 1);
		memset (mMouseBtn, INPUT_KEY_NOT_IN_ACTION, GLFW_MOUSE_BUTTON_LAST + 1);
	}

	bool getKeyDown (const unsigned short& key) {
		if (Input::mKeyboard[key] == INPUT_PRESSED) {
			Input::mKeyboard[key] = INPUT_REPEAT;
			return true;
		}
		return Input::mKeyboard[key] == INPUT_PRESSED;
	}

	bool getKey (const unsigned short& key) {
		return Input::mKeyboard[key] == INPUT_REPEAT || Input::mKeyboard[key] == INPUT_PRESSED;
	}

	bool getKeyUp (const unsigned short& key) {
		return Input::mKeyboard[key] == INPUT_RELEASED;
	}

	bool keyIsUp (const unsigned short& key) {
		return Input::mKeyboard[key] == INPUT_KEY_NOT_IN_ACTION;
	}

	bool keyIsDown (const unsigned short& key) {
		return Input::mKeyboard[key] != INPUT_KEY_NOT_IN_ACTION;
	}

	bool getMouseDown (const unsigned short& btn) {
		return Input::mMouseBtn[btn] == INPUT_PRESSED;
	}

	bool getMouse (const unsigned short& btn) {
		return Input::mMouseBtn[btn] == INPUT_PRESSED || Input::mMouseBtn[btn] == INPUT_REPEAT;
	}

	bool getMouseUp (const unsigned short& btn) {
		return Input::mMouseBtn[btn] == INPUT_RELEASED;
	}

	bool mouseIsUp (const unsigned short& btn) {
		return Input::mMouseBtn[btn] == INPUT_KEY_NOT_IN_ACTION;
	}

	bool mouseIsDown (const unsigned short& btn) {
		return Input::mMouseBtn[btn] != INPUT_KEY_NOT_IN_ACTION;
	}

	float mouseX () { return Input::mMouseX; }

	float mouseY () { return Input::mMouseY; }

	vec2 mousePos () {return {Input::mMouseX, Input::mMouseY}; }

	float mouseScrollX () { return Input::scrollX; }

	float mouseScrollY () { return Input::scrollY; }

	void Input::glfw_key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_UNKNOWN)
			return;

		Input::mKeyboard[key] = action;
		if (action == GLFW_RELEASE) {
			Input::mReleasedKeys.push_back ({ (unsigned short)key, 0 });
		}
	}

	void Input::glfw_mouse_pos_callback (GLFWwindow* window, double x, double y) {
		Input::mMouseX = (float)x;
		Input::mMouseY = (float)y;
	}

	void Input::glfw_mouse_btn_callback (GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			Input::mPressedBtns.push_back({ (unsigned short)button, 0 });
			Input::mMouseBtn[button] = GLFW_PRESS;
		} else {
			Input::mReleasedBtns.push_back({ (unsigned short)button, 0 });
			Input::mMouseBtn[button] = GLFW_RELEASE;
		}
	}

	void Input::glfw_mouse_scroll_callback (GLFWwindow* window, double xoffset, double yoffset) {
		Input::scrollX = (float)xoffset;
		Input::scrollY = (float)yoffset;
	}

	void Input::mDealWithReleasedKeys () {
		auto first = Input::mReleasedKeys.begin();
		auto last = Input::mReleasedKeys.end();
		while (first != last) {
			first->frameCount++;
			if (first->frameCount > 1) {
				Input::mKeyboard[first->key] = INPUT_KEY_NOT_IN_ACTION;
				first = Input::mReleasedKeys.erase(first);
			} else {
				first++;
			}
		}
	}

	void Input::mDealWithReleasedBtns () {
		auto first = Input::mReleasedBtns.begin();
		auto last = Input::mReleasedBtns.end();
		while (first != last) {
			first->frameCount++;
			if (first->frameCount > 1) {
				Input::mMouseBtn[first->btn] = INPUT_KEY_NOT_IN_ACTION;
				first = Input::mReleasedBtns.erase(first);
			} else
				first++;
		}
	}

	void Input::mDealWithPressedBtns () {
		auto first = Input::mPressedBtns.begin();
		auto last = Input::mPressedBtns.end();
		while (first != last) {
			first->frameCount++;
			if (first->frameCount > 1) {
				Input::mMouseBtn[first->btn] = INPUT_REPEAT;
				first = Input::mPressedBtns.erase(first);
			} else
				first++;
		}
	}
}