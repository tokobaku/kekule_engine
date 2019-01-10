#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../maths/kmath.h"
#include <string>

namespace kekule {

	class Window {
	private:
#ifdef _WIN32
		static void* handle;
		static void* csbi;
#endif
		static GLFWwindow* mWindow;
		static int mWidth, mHeight, mPosX, mPosY;
		static std::string mTitle;
		static mat4 mProj;
		static int mExitCode;
		static void (*mOnLoad)();
		static void (*mOnUpdate)(float dt);
		static void (*mOnDraw)();
		static void (*mOnQuit)(int code);
		//TODO: add icon
	public:
		static void init (int width = 640, int height = 480, const std::string& title = "kekule_engine");
		static void init (int width, int height, const std::string& title, int xpos, int ypos);

		static void start ();
		static void exit (int code = 0);
		static void cleanup ();
		static int exitCode ();

		static int width ();
		static int height ();
		static int xPos ();
		static int yPos ();
		static std::string title();
		static mat4 projMat ();

		static void resize (int width, int height);
		static void setPos (int xpos, int ypos);
		static void setTitle (const std::string& title);

		static void setOnLoad (void (*onLoad)());
		static void setOnUpdate (void (*onUpdate)(float dt));
		static void setOnDraw (void (*onDraw)());
		static void setOnQuit (void (*onQuit)(int code));
	};

}