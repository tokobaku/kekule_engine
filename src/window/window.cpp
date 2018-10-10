#define GLEW_STATIC
#include <GL/glew.h>
#include "window.h"
#include <stdlib.h>
#include <cstdio>
#include <cstring>

namespace kekule {

	int Window::mWidth, Window::mHeight, Window::mXpos, Window::mYpos;
	int Window::mExitCode;
	char* Window::mTitle;
	GLFWwindow* Window::mWindow;
	void (*Window::mOnLoad)();
	void (*Window::mOnUpdate)(float dt);
	void (*Window::mOnDraw)();
	void (*Window::mOnQuit)(int exitcode);

	//by default width = 640, height = 480, title = "kekule_engine"
	void Window::init (int width, int height, const char* title) {
		if (glfwInit() != GLFW_TRUE) {
			printf("[GLFW] failed to initialize GLFW\n");
			getchar();
			exit(1);
		}

		mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);

		if (glewInit() != GLEW_OK) {
			printf("[GLEW] failed to initialize GLEW\n");
			getchar();
			exit(1);
		}
		mWidth = width;
		mHeight = height;
		int titlesize = 0;
		while (title[titlesize++]);	//count characters in title including \0
		mTitle = new char[titlesize];
		memcpy(mTitle, title, titlesize * sizeof(char));
	}

	void Window::init (int width, int height, const char* title, int xpos, int ypos) {
		init(width, height, title);
		glfwSetWindowPos(mWindow, xpos, ypos);
	}

	void Window::start () {
		if (*mOnLoad != nullptr)
			mOnLoad();
		
		float startTime = 0.0f;
		float endTime = 0.0f;
		float dt = 0.0f;
		while (!glfwWindowShouldClose(mWindow)) {
			//update deltatime
			dt = endTime - startTime;
			startTime = glfwGetTime();

			if (*mOnUpdate != nullptr)
				mOnUpdate(dt);

			//render
			glClear(GL_COLOR_BUFFER_BIT);

			if (*mOnDraw != nullptr)
				mOnDraw();

			//swap buffers and poll events
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
			endTime = glfwGetTime();
		}
	}

	void Window::terminate () {
		if (*mOnQuit != nullptr)
			mOnQuit(mExitCode);
		glfwTerminate();
	}

	void Window::quit (const int& exitcode) {
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
		mExitCode = exitcode;
	}

	void Window::setOnLoad (void (*onLoad)()) { mOnLoad = onLoad; }
	void Window::setOnUpdate (void (*onUpdate)(float dt)) { mOnUpdate = onUpdate; }
	void Window::setOnDraw (void (*onDraw)()) { mOnDraw = onDraw; }
	void Window::setOnQuit (void (*onQuit)(int exitcode)) { mOnQuit = onQuit; }

}