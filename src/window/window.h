#pragma once
#include <GLFW/glfw3.h>
#include <string>

namespace kekule {

	class Window {
	private:
		static int mWidth, mHeight, mXpos, mYpos;
		static int mExitCode;
		static char* mTitle;
		static GLFWwindow* mWindow;
		static void (*mOnLoad)();
		static void (*mOnUpdate)(float dt);
		static void (*mOnDraw)();
		static void (*mOnQuit)(int exitcode);
		//TODO: add icon and more features (wrap almost whole glfw API)
	public:
		static void init (int width = 640, int height = 480, const char* title = "kekule_engine");
		static void init (int width, int height, const char* title, int xpos, int ypos);
		static void start ();
		static void terminate ();

		static void quit (const int& exitcode);

		static void setOnLoad (void (*onLoad)());
		static void setOnUpdate (void (*onUpdate)(float dt));
		static void setOnDraw (void (*onDraw)());
		static void setOnQuit (void (*onQuit)(int exitcode));
	};
	
}