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

using namespace kekule;

Line l;
Line l1;
Triangle t;

int main () {
	Window::init();
	l = Line(vec2(-0.5f, -0.5f), vec2(0.5f, 0.5f), Color(255, 0, 255));
	l1 = Line(vec2(0.5f, -0.5f), vec2(-0.5f, 0.5f), Color(255, 0, 0));
	l1.layer = 1;
	t = Triangle(vec2(-0.5f), vec2(0.0f, 0.5f), vec2(0.5f, -0.5f), Color(255, 128, 0));

	Window::setOnDraw([]() {
		l.render();
		l1.render();
		t.render();
		if (getMouseDown(INPUT_MOUSE_1))
			l.layer = 1;
		else if (getMouseDown(INPUT_MOUSE_2))
			l.layer = -1;
		if (getKey(INPUT_ESCAPE))
			Window::exit();
	});
	Window::start();
	return Window::exitCode();
}