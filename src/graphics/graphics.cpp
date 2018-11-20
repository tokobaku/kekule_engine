#include "shader.h"
#include "graphics.h"

namespace kekule {

	void Line::glRender () const {}

	Line::Line ()
		:IRenderable(), mVbo(), mVao(), head(0.0f), tail(0.0f), color(0) {}
	
	Line::Line (const vec2& head, const vec2& tail, const Color& color)
		:IRenderable(), mVbo(), mVao(), head(head), tail(tail), color(color) {}
	
	Line::Line (const Line& other)
		:IRenderable(), mVbo(), mVao(), head(other.head), tail(other.tail), color(other.color) {}
	
	Line::~Line () {}

	void Line::render () const {
		mVao.bind();
		if (!mVbo)
			mVbo.setData(2, {head.x, head.y, tail.x, tail.y});
		else
			mVbo.setSubData(0, {head.x, head.y, tail.x, tail.y});
		
		mVao.specifyLayout(0, 2, 2, 0);
		glDrawArrays(GL_LINES, 0, 2);
	}
	
}