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

Circle c;

int main () {
	Window::init();
	c = Circle(100.0f, 40.0f);
	Window::setOnDraw([]() {
		c.render();
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