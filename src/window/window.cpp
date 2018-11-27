#define GLEW_STATIC
#include "window.h"
#include "input.h"
#include "logging.h"
#include "../graphics/renderer.h"
#include "../graphics/shader.h"
#include "../graphics/camera.h"

#include <chrono>

namespace kekule {

	GLFWwindow* Window::mWindow;
	int Window::mWidth, Window::mHeight, Window::mPosX, Window::mPosY;
	std::string Window::mTitle;
	mat4 Window::mProj;
	int Window::mExitCode;
	void (*Window::mOnLoad)();
	void (*Window::mOnUpdate)(float dt);
	void (*Window::mOnDraw)();
	void (*Window::mOnQuit)(int code);

	void Window::init (int width, int height, const std::string& title) {
		mExitCode = 0;
		mWidth = width;
		mHeight = height;
		mTitle = title;
		if (glfwInit() != GLFW_TRUE) {
			logError("[GLFW] failed to initialize GLFW");
			getchar();
			Window::exit(1);
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);

		if (glewInit() != GLEW_OK) {
			logError("[GLEW] failed to initialize GLEW");
			getchar();
			Window::exit(1);
		}

		mProj = mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
		Shader::simple().bind();
		Shader::simple().setUniformMat4("proj", mProj);

		glfwSetKeyCallback(mWindow, Input::glfw_key_callback);
		glfwSetMouseButtonCallback(mWindow, Input::glfw_mouse_btn_callback);
		glfwSetCursorPosCallback(mWindow, Input::glfw_mouse_pos_callback);
		glfwSetScrollCallback(mWindow, Input::glfw_mouse_scroll_callback);
	}

	void Window::init (int width, int height, const std::string& title, int xpos, int ypos) {
		init(width, height, title);
		Window::setPos(xpos, ypos);
	}

	void Window::start () {
		Input::init();

		if (mOnLoad != nullptr)
			mOnLoad();
		
		float lastFrame = 0.0f;
		float dt = 0.0f;
		while (!glfwWindowShouldClose(mWindow)) {
			dt = glfwGetTime() - lastFrame;
			lastFrame = glfwGetTime();

			//Logic
			if (*mOnUpdate != nullptr)
				mOnUpdate(dt);

			//Render
			GL(glClear(GL_COLOR_BUFFER_BIT));
			if (*mOnDraw != nullptr)
				mOnDraw();

			Camera::updateViewMatrix();
			
			Renderer::render();

			glfwSwapBuffers(mWindow);
			glfwPollEvents();

			Input::mDealWithPressedBtns();
			Input::mDealWithReleasedBtns();
			Input::mDealWithReleasedKeys();
		}
	}

	int Window::exitCode () { return mExitCode; }

	void Window::exit (int code) {
		mExitCode = code;
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
	}

	int Window::width () { return mWidth; }
	int Window::height () { return mHeight; }
	int Window::xPos () { return mPosX; }
	int Window::yPos () { return mPosY; }
	std::string Window::title () { return mTitle; }
	mat4 Window::projMat () { return mProj; }

	void Window::resize (int width, int height) {
		mWidth = width;
		mHeight = height;
		glfwSetWindowSize(mWindow, width, height);
		glViewport(0, 0, width, height);
		mProj = mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
		Shader::simple().bind();
		Shader::simple().setUniformMat4("proj", mProj);
	}

	void Window::setPos (int xpos, int ypos) {
		mPosX = xpos;
		mPosY = ypos;
		glfwSetWindowPos(mWindow, xpos, ypos);
	}

	void Window::setTitle (const std::string& title) {
		mTitle = title;
		glfwSetWindowTitle(mWindow, mTitle.c_str());
	}

	void Window::setOnLoad (void (*onLoad)()) {
		mOnLoad = onLoad;
	}

	void Window::setOnUpdate (void (*onUpdate)(float dt)) {
		mOnUpdate = onUpdate;
	}

	void Window::setOnDraw (void (*onDraw)()) {
		mOnDraw = onDraw;
	}

	void Window::setOnQuit (void (*onQuit)(int code)) {
		mOnQuit = onQuit;
	}
}