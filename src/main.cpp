#include "window/window.h"
#include "window/logging.h"
#include "window/input.h"
#include <iostream>
#include "maths/kmath.h"

using namespace kekule;

int main () {
	Window::init();
	Window::start();
	return Window::exitCode();
}