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

Polygon p;

int main () {
	Window::init();
	p = Polygon({0.0f, 0.0f, 100.0f, 0.0f, 100.0f, 100.0f, 0.0f, 100.0f});
	p.color = Color(255, 255, 0);
	p.mode = KEKULE_WIREFRAME;
	Window::setOnDraw([]() {
		p.render();
		if (getKeyDown(INPUT_SPACE)) {
			p.verts.push_back(rand() % 640);
			p.verts.push_back(rand() % 480);
		}
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