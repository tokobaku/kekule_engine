#include "shader.h"
#include "graphics.h"
#include "../window/input.h"

namespace kekule {

	Line::Line ()
		:IRenderable(), mVbo(), mVao(), head(0.0f), tail(0.0f), color(0), width(1.0f), pivot(0.0f), angle(0.0f) {}
	
	Line::Line (const vec2& head, const vec2& tail, const Color& color)
		:IRenderable(), mVbo(), mVao(), head(head), tail(tail), color(color), width(1.0f), angle(0.0f)
	{
		pivot = (head + tail) / 2;
		mVao.bind();
		mVbo = VertexBuffer(2, {head.x, head.y, tail.x, tail.y});
		mVbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Line::Line (const Line& other)
		:IRenderable()
		,mVbo(), mVao()
		,head(other.head)
		,tail(other.tail)
		,color(other.color)
		,width(other.width)
		,pivot(other.pivot)
		,angle(other.angle)
	{
		mVao.bind();
		mVbo.setData(2, {head.x, head.y, tail.x, tail.y});
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Line::~Line () {}

	Line& Line::operator= (const Line& other) {
		layer = other.layer;
		head = other.head;
		tail = other.tail;
		color = other.color;
		pivot = other.pivot;
		angle = other.angle;
		mVao.bind();
		mVbo.setData(2, {head.x, head.y, tail.x, tail.y});
		mVao.specifyLayout(0, 2, 2, 0);
		return *this;
	}

	void Line::glRender () const {
		GL(glLineWidth(width));
		mVao.bind();
		mVbo.setSubData(0, {head.x, head.y, tail.x, tail.y});
		Shader::simple().bind();
		Shader::simple().setUniform("color", color.toVec4());
		mat4 model = mat4::translation(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		Shader::simple().setUniformMat4("model", model);
		GL(glDrawArrays(GL_LINES, 0, 2));
		GL(glLineWidth(1.0f));
	}

	Triangle::Triangle ()
		:IRenderable(), mVbo(), mVao(), p1(0.0f), p2(0.0f), p3(0.0f), color(0), mode(KEKULE_FILL), pivot(0.0f), angle(0.0f) {}
	
	Triangle::Triangle (const vec2& pos1, const vec2& pos2, const vec2& pos3, const Color& color)
		:IRenderable(), mVbo(), mVao(), p1(pos1), p2(pos2), p3(pos3), color(color), mode(KEKULE_FILL), angle(0.0f)
	{
		pivot = (p1 + p2 + p3) / 3.0f;
		mVbo.setData(2, {p1.x, p1.y, p2.x, p2.y, p3.x, p3.y});
		mVao.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Triangle::Triangle (const Triangle& other)
		:IRenderable(other.layer)
		,mVbo()
		,mVao()
		,p1(other.p1)
		,p2(other.p2)
		,p3(other.p3)
		,color(other.color)
		,mode(other.mode)
		,pivot(other.pivot)
		,angle(other.angle)
	{
		mVbo.setData(2, {p1.x, p1.y, p2.x, p2.y, p3.x, p3.y});
		mVao.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Triangle::~Triangle () {}

	Triangle& Triangle::operator= (const Triangle& other) {
		layer = other.layer;
		p1 = other.p1;
		p2 = other.p2;
		p3 = other.p3;
		color = other.color;
		mode = other.mode;
		pivot = other.pivot;
		angle = other.angle;
		mVao.bind();
		mVbo.setData(2, {p1.x, p1.y, p2.x, p2.y, p3.x, p3.y});
		mVao.specifyLayout(0, 2, 2, 0);
		return *this;
	}

	void Triangle::render () const { IRenderable::render(); }
	void Triangle::render (const int& layer) const { IRenderable::render(layer); }
	void Triangle::render (const unsigned char& mode, const int& layer) const {
		this->mode = mode;
		IRenderable::render(layer);
	}

	void Triangle::glRender () const {
		mVbo.setSubData(0, {p1.x, p1.y, p2.x, p2.y, p3.x, p3.y});
		mVao.bind();
		Shader::simple().bind();
		Shader::simple().setUniform("color", color.toVec4());
		mat4 model = mat4::translation(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		Shader::simple().setUniformMat4("model", model);
		switch (mode) {
		case KEKULE_FILL:
			GL(glDrawArrays(GL_TRIANGLES, 0, 3));
		case KEKULE_LINE:
		case KEKULE_WIREFRAME:
			GL(glDrawArrays(GL_LINE_LOOP, 0, 3));
			break;
		default:
			logError("[kekule_engine] invalid draw mode for Triangle");
		}
	}

	Rect::Rect ()
		:pos(0.0f), width(0.0f), height(0.0f), color(0), mode(0), pivot(0.0f), angle(0.0f) {}
	
	Rect::Rect (const vec2& pos, const float& width, const float& height, const Color& c)
		:pos(pos), width(width), height(height), color(c), mode(0), angle(0.0f)
	{
		pivot = pos + vec2(width/2, height/2);
		mVao.bind();
		mVbo.setData(2, {pos.x, pos.y, pos.x + width, pos.y,
						pos.x + width, pos.y + height, pos.x, pos.y + height});
		mVao.specifyLayout(0, 2, 2, 0);
	}

	Rect::Rect (const Rect& other)
		:IRenderable(other.layer)
		,pos(other.pos)
		,width(other.width)
		,height(other.height)
		,color(other.color)
		,mode(other.mode)
		,pivot(other.pivot)
		,angle(other.angle)
	{
		mVao.bind();
		mVao.bind();
		mVbo.setData(2, {pos.x, pos.y, pos.x + width, pos.y,
						pos.x + width, pos.y + height, pos.x, pos.y + height});
		mVao.specifyLayout(0, 2, 2, 0);
	}

	Rect::~Rect () {}

	Rect& Rect::operator= (const Rect& other) {
		layer = other.layer;
		pos = other.pos;
		width = other.width;
		height = other.height;
		color = other.color;
		mode = other.mode;
		pivot = other.pivot;
		angle = other.angle;
		mVao.bind();
		mVbo.setData(2, {pos.x, pos.y, pos.x + width, pos.y,
						pos.x + width, pos.y + height, pos.x, pos.y + height});
		mVao.specifyLayout(0, 2, 2, 0);
		return *this;
	}

	void Rect::render () const { IRenderable::render(); }
	void Rect::render (const int& layer) const { IRenderable::render(layer); }
	void Rect::render (const unsigned char& mode, const int& layer) const {
		this->mode = mode;
		IRenderable::render(layer);
	}

	void Rect::glRender () const {
		mVbo.setSubData(0, {pos.x, pos.y, pos.x + width, pos.y,
						pos.x + width, pos.y + height, pos.x, pos.y + height});
		mVao.bind();
		Shader::simple().bind();
		Shader::simple().setUniform("color", color.toVec4());
		mat4 model = mat4::translation(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		Shader::simple().setUniformMat4("model", model);
		switch (mode) {
		case KEKULE_FILL:
			GL(glDrawArrays(GL_QUADS, 0, 4));
			break;
		case KEKULE_LINE:
			GL(glDrawArrays(GL_LINE_LOOP, 0, 4));
			break;
		case KEKULE_WIREFRAME:
			GL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			GL(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
			GL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			break;
		default:
			logError("[kekule_engine] invalid draw mode for Rect");
		}
	}
	
}