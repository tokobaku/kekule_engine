#define GLEW_STATIC
#include <GL/glew.h>
#include "window/window.h"
#include "window/logging.h"
#include "window/input.h"
#include <iostream>
#include "maths/kmath.h"
#include "graphics/shader.h"
#include "graphics/buffer_objects.h"
#include "graphics/renderable.h"
#include "graphics/graphics.h"
#include "graphics/renderable.h"
#include "graphics/camera.h"
#include <random>

using namespace kekule;

Rect r[2500];

int main () {
	Window::init();
	for (int i = 0; i < 2500; ++i)
		r[i] = Rect(vec2(rand() % 640, rand() % 480), 10, 10, Color(rand() % 255, rand() % 255, rand() % 255));
	Window::setOnDraw([]() {
		for (int i = 0; i < 2500; ++i)
			r[i].render();
		if (getKey(INPUT_ESCAPE))
			Window::exit();
	});
	Window::setOnUpdate([](float dt) {
		static float t = 0.0f;
		static int frames = 0;
		t += dt;
		frames++;
		if (t >= 1.0f) {
			LOGI << frames << '\n';
			t = 0.0f;
			frames = 0;
		}
	});
	Window::start();
	Window::cleanup();
	return Window::exitCode();
}