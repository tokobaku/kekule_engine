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

using namespace kekule;

Shader s;
VertexBuffer vbo;
IndexBuffer ibo;
VertexArray vao;
Line l;

int main () {
	Window::init();
	s = Shader("../src/graphics/shaders/simple.vert", "../src/graphics/shaders/simple.frag", "simple");
	s.bind();
	vbo = VertexBuffer(2, {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f});
	ibo = IndexBuffer({0, 1, 2, 0, 2, 3});
	vao.bind();
	vao.specifyLayout(0, 2, 2, 0);
	vao.unbind();
	l = Line(vec2(-0.5f), vec2(0.5f), Color(255));

	Window::setOnDraw([]() {
		l.render();
		//vao.bind();
		//glDrawElements(GL_TRIANGLES, ibo.indCount(), GL_UNSIGNED_INT, 0);
		if (getKey(INPUT_ESCAPE))
			Window::exit();
	});
	Window::start();
	return Window::exitCode();
}