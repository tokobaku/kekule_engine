#include "camera.h"
#include "shader.h"

namespace kekule {

	mat4 Camera::mView;

	void Camera::updateViewMatrix () {
		Shader::simple().bind();
		mView = mat4::translation(-pos);
		Shader::simple().setUniformMat4("view", mView);
	}

	vec2 Camera::pos {0.0f};
	
}