#include "window/window.h"
#include "maths/kmath.h"
#include "graphics/graphics.h"
#include "graphics/camera.h"
#include <iostream>
#include <random>

using namespace kekule;

Circle c;

int main () {
	Window::init();
	c = Circle(vec2(320.0f, 240.0f), 200.0f);
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