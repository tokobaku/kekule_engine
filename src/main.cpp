#include "window/window.h"

using namespace kekule;

int main () {
	Window::setOnDraw([]() {
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
	});
	Window::setOnLoad([]() {
		printf("Loaded\n");
	});
	Window::setOnUpdate([](float dt){
		printf("%f\n", 1.0f / dt);
	});
	Window::init();
	Window::start();
	Window::terminate();
}