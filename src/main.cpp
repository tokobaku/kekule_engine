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

using namespace kekule;

Rect r;

int main () {
	Window::init();
	r = Rect(vec2(Window::width() / 2, Window::height() / 2) - 50.0f, 100.0f, 100.0f);
	Window::setOnDraw([]() {
		r.render();
		if (getKey(INPUT_ESCAPE))
			Window::exit();
	});
	Window::setOnUpdate([](float dt) {
		r.angle += dt * 100.0f;
		static float t = 0.0f;
		static int frames = 0;
		t += dt;
		frames++;
		if (t >= 1.0f) {
			logInfo(frames);
			t = 0.0f;
			frames = 0;
		}
	});
	Window::start();
	return Window::exitCode();
}
