#pragma once

#include "../maths/kmath.h"

namespace kekule
{
	class Camera {
		friend class Window;
	private:
		static mat4 mView;

		static void updateViewMatrix ();
	public:
		static vec2 pos;
	};
}