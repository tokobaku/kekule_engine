#include "shader.h"
#include "graphics.h"
#include "../window/input.h"

namespace kekule {

	Line::Line ()
		:IRenderable(), mVbo(), mVao(), head(0.0f), tail(0.0f), color(0), width(1.0f) {}
	
	Line::Line (const vec2& head, const vec2& tail, const Color& color)
		:IRenderable(), mVbo(), mVao(), head(head), tail(tail), color(color), width(1.0f)
	{
		mVao.bind();
		mVbo = VertexBuffer(2, {head.x, head.y, tail.x, tail.y});
		mVbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Line::Line (const Line& other)
		:IRenderable(), mVbo(), mVao(), head(other.head), tail(other.tail), color(other.color), width(other.width)
	{
		mVao.bind();
		mVbo.setData(2, {head.x, head.y, tail.x, tail.y});
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Line::~Line () {}

	void Line::glRender () const {
		GL(glLineWidth(width));
		mVao.bind();
		mVbo.setSubData(0, {head.x, head.y, tail.x, tail.y});
		Shader::simple().bind();
		Shader::simple().setUniform("color", color.toVec4());
		GL(glDrawArrays(GL_LINES, 0, 2));
		GL(glLineWidth(1.0f));
	}

	Triangle::Triangle ()
		:IRenderable(), mVbo(), mVao(), pos1(0.0f), pos2(0.0f), pos3(0.0f), color(0), mode(KEKULE_FILL) {}
	
	Triangle::Triangle (const vec2& pos1, const vec2& pos2, const vec2& pos3, const Color& color)
		:IRenderable(), mVbo(), mVao(), pos1(pos1), pos2(pos2), pos3(pos3), color(color), mode(KEKULE_FILL)
	{
		mVbo.setData(2, {pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y});
		mVao.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Triangle::Triangle (const Triangle& other)
		:IRenderable(other.layer)
		,mVbo()
		,mVao()
		,pos1(other.pos1)
		,pos2(other.pos2)
		,pos3(other.pos3)
		,color(other.color)
		,mode(other.mode)
	{
		mVbo.setData(2, {pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y});
		mVao.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Triangle::~Triangle () {}

	void Triangle::render () const { IRenderable::render(); }
	void Triangle::render (const int& layer) const { IRenderable::render(layer); }
	void Triangle::render (const unsigned char& mode, const int& layer) const {
		this->mode = mode;
		IRenderable::render(layer);
	}

	void Triangle::glRender () const {
		mVbo.setSubData(0, {pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y});
		mVao.bind();
		Shader::simple().bind();
		Shader::simple().setUniform("color", color.toVec4());
		if (mode == KEKULE_FILL) {
			GL(glDrawArrays(GL_TRIANGLES, 0, 3));
		} else {
			GL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			GL(glDrawArrays(GL_TRIANGLES, 0, 3));
			GL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
	}
	
}