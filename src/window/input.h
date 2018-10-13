#pragma once
#include "window.h"
#include "../maths/kmath.h"
#include <list>

#define KEKULE_KBD_BTN_COUNT	GLFW_KEY_LAST
#define KEKULE_MOUSE_BTN_COUNT	GLFW_MOUSE_BUTTON_LAST

#define GLFW_KEY_UNKNOWN            -1

/* Key Codes are same as GLFW keycodes (INPUT_SPACE == GLFW_KEY_SPACE) */
/* Printable keys */
#define INPUT_SPACE              32
#define INPUT_APOSTROPHE         39  /* ' */
#define INPUT_COMMA              44  /* , */
#define INPUT_MINUS              45  /* - */
#define INPUT_PERIOD             46  /* . */
#define INPUT_SLASH              47  /* / */
#define INPUT_0                  48
#define INPUT_1                  49
#define INPUT_2                  50
#define INPUT_3                  51
#define INPUT_4                  52
#define INPUT_5                  53
#define INPUT_6                  54
#define INPUT_7                  55
#define INPUT_8                  56
#define INPUT_9                  57
#define INPUT_SEMICOLON          59  /* ; */
#define INPUT_EQUAL              61  /* = */
#define INPUT_A                  65
#define INPUT_B                  66
#define INPUT_C                  67
#define INPUT_D                  68
#define INPUT_E                  69
#define INPUT_F                  70
#define INPUT_G                  71
#define INPUT_H                  72
#define INPUT_I                  73
#define INPUT_J                  74
#define INPUT_K                  75
#define INPUT_L                  76
#define INPUT_M                  77
#define INPUT_N                  78
#define INPUT_O                  79
#define INPUT_P                  80
#define INPUT_Q                  81
#define INPUT_R                  82
#define INPUT_S                  83
#define INPUT_T                  84
#define INPUT_U                  85
#define INPUT_V                  86
#define INPUT_W                  87
#define INPUT_X                  88
#define INPUT_Y                  89
#define INPUT_Z                  90
#define INPUT_LEFT_BRACKET       91  /* [ */
#define INPUT_BACKSLASH          92  /* \ */
#define INPUT_RIGHT_BRACKET      93  /* ] */
#define INPUT_GRAVE_ACCENT       96  /* ` */
#define INPUT_WORLD_1            161 /* non-US #1 */
#define INPUT_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define INPUT_ESCAPE             256
#define INPUT_ENTER              257
#define INPUT_TAB                258
#define INPUT_BACKSPACE          259
#define INPUT_INSERT             260
#define INPUT_DELETE             261
#define INPUT_RIGHT              262
#define INPUT_LEFT               263
#define INPUT_DOWN               264
#define INPUT_UP                 265
#define INPUT_PAGE_UP            266
#define INPUT_PAGE_DOWN          267
#define INPUT_HOME               268
#define INPUT_END                269
#define INPUT_CAPS_LOCK          280
#define INPUT_SCROLL_LOCK        281
#define INPUT_NUM_LOCK           282
#define INPUT_PRINT_SCREEN       283
#define INPUT_PAUSE              284
#define INPUT_F1                 290
#define INPUT_F2                 291
#define INPUT_F3                 292
#define INPUT_F4                 293
#define INPUT_F5                 294
#define INPUT_F6                 295
#define INPUT_F7                 296
#define INPUT_F8                 297
#define INPUT_F9                 298
#define INPUT_F10                299
#define INPUT_F11                300
#define INPUT_F12                301
#define INPUT_F13                302
#define INPUT_F14                303
#define INPUT_F15                304
#define INPUT_F16                305
#define INPUT_F17                306
#define INPUT_F18                307
#define INPUT_F19                308
#define INPUT_F20                309
#define INPUT_F21                310
#define INPUT_F22                311
#define INPUT_F23                312
#define INPUT_F24                313
#define INPUT_F25                314
#define INPUT_KP_0               320
#define INPUT_KP_1               321
#define INPUT_KP_2               322
#define INPUT_KP_3               323
#define INPUT_KP_4               324
#define INPUT_KP_5               325
#define INPUT_KP_6               326
#define INPUT_KP_7               327
#define INPUT_KP_8               328
#define INPUT_KP_9               329
#define INPUT_KP_DECIMAL         330
#define INPUT_KP_DIVIDE          331
#define INPUT_KP_MULTIPLY        332
#define INPUT_KP_SUBTRACT        333
#define INPUT_KP_ADD             334
#define INPUT_KP_ENTER           335
#define INPUT_KP_EQUAL           336
#define INPUT_LEFT_SHIFT         340
#define INPUT_LEFT_CONTROL       341
#define INPUT_LEFT_ALT           342
#define INPUT_LEFT_SUPER         343
#define INPUT_RIGHT_SHIFT        344
#define INPUT_RIGHT_CONTROL      345
#define INPUT_RIGHT_ALT          346
#define INPUT_RIGHT_SUPER        347
#define INPUT_MENU               348

/* Mouse Input */
/* Buttons are same as GLFW buttons (INPUT_MOUSE_1 = GLFW_MOUSE_BUTTON_1)*/
#define INPUT_MOUSE_1         0
#define INPUT_MOUSE_2         1
#define INPUT_MOUSE_3         2
#define INPUT_MOUSE_4         3
#define INPUT_MOUSE_5         4
#define INPUT_MOUSE_6         5
#define INPUT_MOUSE_7         6
#define INPUT_MOUSE_8         7
#define INPUT_MOUSE_LEFT      INPUT_MOUSE_1
#define INPUT_MOUSE_RIGHT     INPUT_MOUSE_2
#define INPUT_MOUSE_MIDDLE    INPUT_MOUSE_3

#define INPUT_PRESSED		GLFW_PRESS		//key has been pressed
#define INPUT_REPEAT		GLFW_REPEAT		//key is being pressed
#define INPUT_RELEASED		GLFW_RELEASE	//key has been released
#define INPUT_KEY_NOT_IN_ACTION	3

namespace kekule {
	class Window;

	class Input {
	private:
		struct ReleasedKey {
			union {
				unsigned short key;
				unsigned short btn;
			};
			unsigned char frameCount;
		};
		typedef ReleasedKey ReleasedBtn;
		typedef ReleasedBtn PressedBtn;
	private:
		static unsigned char* mKeyboard;		//size = GLFW_KEY_LAST + 1
		static unsigned char* mMouseBtn;		//size = GLFW_BUTTON_LAST + 1
		static float mMouseX, mMouseY, scrollX, scrollY;
		static std::list<ReleasedKey> mReleasedKeys;
		static std::list<ReleasedBtn> mReleasedBtns;
		static std::list<PressedBtn>  mPressedBtns;

		static void init ();
		static void mDealWithReleasedKeys ();
		static void mDealWithPressedBtns ();
		static void mDealWithReleasedBtns ();
		//required by GLFW
		//sets key states
		static void glfw_key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);

		//required by GLFW
		//sets mMouseX and mMouseY values
		static void glfw_mouse_pos_callback (GLFWwindow* window, double x, double y);

		//required by GLFW
		//sets mouse button states
		static void glfw_mouse_btn_callback (GLFWwindow* window, int button, int action, int mods);

		//required by GLFW
		//captures mouse scroll
		static void glfw_mouse_scroll_callback (GLFWwindow* window, double xoffset, double yoffset);
	public:

		//returns true if the state of key has been changed to "pressed" during current loop
		//use INPUT_KEYNAME enums instead of literals (recommended)
		friend bool getKeyDown (const unsigned short& key);

		//return true if the state of key has been changed to "released" during current loop
		friend bool getKeyUp (const unsigned short& key);

		//return true if key is pressed
		friend bool getKey (const unsigned short& key);

		//returns true if key is released
		friend bool keyIsUp (const unsigned short& key);

		//returns true if the state of mouse button has been chaenged to "pressed" during current loop
		friend bool getMouseDown (const unsigned short& btn);

		//retuns true if mouse button is pressed
		friend bool getMouse (const unsigned short& btn);

		//return true if state of the mouse button has been changed to "released" during current loop
		friend bool getMouseUp (const unsigned short& btn);

		//return true if mouse button is up
		friend bool mouseIsUp (const unsigned short& btn);
		
		//returns mouseX position
		friend float mouseX ();
		
		//returns mouseY position
		friend float mouseY ();

		//return mouse position
		friend vec2 mousePos ();

		friend float mouseScrollX ();
		friend float mouseScrollY ();
		
		//static maths::vec2 mousePos ();

		friend class Window;
	};

	bool getKeyDown (const unsigned short& key);
	bool getKeyUp (const unsigned short& key);
	bool getKey (const unsigned short& key);
	bool keyIsUp (const unsigned short& key);
	bool getMouseDown (const unsigned short& btn);
	bool getMouse (const unsigned short& btn);
	bool getMouseUp (const unsigned short& btn);
	bool mouseIsUp (const unsigned short& btn);
	float mouseX ();
	float mouseY ();
	vec2 mousePos ();
}