#include "shader.h"
#include "graphics.h"
#include "../window/input.h"

namespace kekule {

	Line::Line ()
		:head(0.0f), tail(0.0f), color(0), width(1.0f), pivot(0.0f), scale(1.0f), angle(0.0f) {}
	
	Line::Line (const vec2& head, const vec2& tail, const Color& color)
		:head(head), tail(tail), color(color), width(1.0f), scale(1.0f), angle(0.0f)
	{
		pivot = (head + tail) / 2;
		mVao.bind();
		mVbo = VertexBuffer(2, {head.x, head.y, tail.x, tail.y});
		mVbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Line::Line (const Line& other)
		:IRenderable()
		,mVbo()
		,mVao()
		,head(other.head)
		,tail(other.tail)
		,color(other.color)
		,width(other.width)
		,pivot(other.pivot)
		,scale(other.scale)
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
		scale = other.scale;
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
		mat4 model(1.0f);
		model.translate(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		model.scale(scale);
		Shader::simple().setUniformMat4("model", model);
		GL(glDrawArrays(GL_LINES, 0, 2));
		GL(glLineWidth(1.0f));
	}

	PolyLine::PolyLine ()
		:pos(0.0f), scale(1.0f), pivot(0.0f), color(0), angle(0.0f), width(1.0f) {}
	
	PolyLine::PolyLine (const std::vector<float>& verts, const Color& color)
		:pos(0.0f), scale(1.0f), pivot(0.0f), color(color), angle(0.0f), width(1.0f)
	{
		this->verts.resize(verts.size() / 2);
		memcpy(this->verts.data(), verts.data(), verts.size() * sizeof(float));
		mVao.bind();
		mVbo.setData(2, this->verts.size(), (const float*)this->verts.data());
		mVao.specifyLayout(0, 2, 2, 0);
	}

	PolyLine::PolyLine (const PolyLine& other)
		:IRenderable(other.layer)
		,verts(other.verts)
		,pos(other.pos)
		,scale(other.scale)
		,pivot(other.pivot)
		,color(other.color)
		,angle(other.angle)
		,width(other.width)
	{
		VertexBuffer::clone(other.mVbo, mVbo);
		mVao.bind();
		mVbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}

	PolyLine::~PolyLine () {}

	PolyLine& PolyLine::operator= (const PolyLine& other) {
		layer = other.layer;
		verts = other.verts;
		pos = other.pos;
		scale = other.scale;
		pivot = other.pivot;
		color = other.color;
		angle = other.angle;
		width = other.width;
		VertexBuffer::clone(other.mVbo, mVbo);
		mVao.bind();
		mVbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
		return *this;
	}

	void PolyLine::centerPivot () {
		pivot = 0.0f;
		for (auto m : verts)
			pivot += m;
		pivot /= verts.size();
	}

	void PolyLine::glRender () const {
		if (verts.size() <= mVbo.vertCount())
			mVbo.setSubData(0, verts.size(), (const float*)verts.data());
		else
			mVbo.setData(2, verts.size(), (const float*)verts.data());
		mVao.bind();
		Shader::simple().bind();
		mat4 model(1.0f);
		model.translate(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		model.translate(pos);
		model.scale(scale);
		Shader::simple().setUniformMat4("model", model);
		Shader::simple().setUniform("color", color.toVec4());
		GL(glLineWidth(width));
		GL(glDrawArrays(GL_LINE_STRIP, 0, mVbo.vertCount()));
		GL(glLineWidth(1.0));
	}

	Triangle::Triangle ()
		:p1(0.0f)
		,p2(0.0f)
		,p3(0.0f)
		,color(0)
		,mode(KEKULE_FILL)
		,pivot(0.0f)
		,scale(1.0f)
		,pos(0.0f)
		,angle(0.0f) {}
	
	Triangle::Triangle (const vec2& pos1, const vec2& pos2, const vec2& pos3, const Color& color)
		:p1(pos1)
		,p2(pos2)
		,p3(pos3)
		,color(color)
		,mode(KEKULE_FILL)
		,scale(1.0f)
		,angle(0.0f)
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
		,scale(other.scale)
		,angle(other.angle)
	{
		mVao.bind();
		mVbo.setData(2, {p1.x, p1.y, p2.x, p2.y, p3.x, p3.y});
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
		scale = other.scale;
		pos = other.pos;
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
		mVbo.setSubData(0, { p1.x, p1.y, p2.x, p2.y, p3.x, p3.y });
		mVao.bind();
		Shader::simple().bind();
		Shader::simple().setUniform("color", color.toVec4());
		mat4 model(1.0f);
		model.translate(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		model.translate(pos);
		model.scale(scale);
		Shader::simple().setUniformMat4("model", model);
		switch (mode) {
		case KEKULE_FILL:
			GL(glDrawArrays(GL_TRIANGLES, 0, 3));
		case KEKULE_LINE:
		case KEKULE_WIREFRAME:
			GL(glDrawArrays(GL_LINE_LOOP, 0, 3));
			break;
		default:
			LOGE << "[kekule_engine] invalid draw mode for Triangle\n";
		}
	}

	VertexBuffer Rect::mVbo;
	VertexArray Rect::mVao;

	Rect::Rect ()
		:pos(0.0f)
		,width(0.0f)
		,height(0.0f)
		,color(0)
		,mode(0)
		,pivot(0.0f)
		,angle(0.0f) {}
	
	Rect::Rect (const vec2& pos, const float& width, const float& height, const Color& c)
		:pos(pos), width(width), height(height), color(c), mode(0), angle(0.0f)
	{
		if (mVao == nullptr) {
			mVao.bind();
			mVbo.setData(2, {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f});
			mVao.specifyLayout(0, 2, 2, 0);
		}
		pivot = pos + vec2(width/2, height/2);
	}

	Rect::Rect (const Rect& other)
		:IRenderable(other.layer)
		,pos(other.pos)
		,width(other.width)
		,height(other.height)
		,color(other.color)
		,mode(other.mode)
		,pivot(other.pivot)
		,angle(other.angle) {}

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
		return *this;
	}

	void Rect::render () const { IRenderable::render(); }
	void Rect::render (const int& layer) const { IRenderable::render(layer); }
	void Rect::render (const unsigned char& mode, const int& layer) const {
		this->mode = mode;
		IRenderable::render(layer);
	}

	void Rect::glRender () const {
		mVao.bind();
		Shader::simple().bind();
		Shader::simple().setUniform("color", color.toVec4());
		mat4 model(1.0f);
		model.translate(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		model.translate(pos);
		model.scale({width, height});
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

	Polygon::Polygon ()
		:color(0), pos(0.0f), pivot(0.0f), angle(0.0f), scale(1.0f), mode(KEKULE_FILL) {}
	
	Polygon::Polygon (std::initializer_list<float> verts, std::initializer_list<uint> inds, const Color& c)
		:color(c)
		,pos(0.0f)
		,pivot(0.0f)
		,angle(0.0f)
		,scale(1.0f)
		,verts(verts)
		,inds(inds)
		,mode(KEKULE_FILL)
	{
		mVao.bind();
		mVbo.setData(2, verts);
		mIbo.setData(inds);
		mVao.specifyLayout(0, 2, 2, 0);
		centerPivot();
	}

	Polygon::Polygon (const uint& vertCount, const float* vertData, const uint& indCount, const uint* indData, const Color& c)
		:color(c), pos(0.0f), pivot(0.0f), angle(0.0f), scale(1.0f), mode(KEKULE_FILL)
	{
		verts = {vertData, vertData + vertCount};
		inds = {indData, indData + indCount};
		mVao.bind();
		mVbo.setData(2, vertCount, (const float*)vertData);
		mIbo.setData(indCount, indData);
		mVao.specifyLayout(0, 2, 2, 0);
	}

	Polygon::Polygon (const Polygon& other)
		:IRenderable(other.layer)
		,color(other.color)
		,pos(other.pos)
		,pivot(other.pivot)
		,angle(other.angle)
		,scale(other.scale)
		,verts(other.verts)
		,inds(other.inds)
		,mode(other.mode)
	{
		VertexBuffer::clone(other.mVbo, mVbo);
		IndexBuffer::clone(other.mIbo, mIbo);
		mVao.bind();
		mVbo.bind();
		mIbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}

	Polygon::~Polygon () {}

	Polygon& Polygon::operator= (const Polygon& other) {
		layer = other.layer;
		color = other.color;
		pos = other.pos;
		pivot = other.pivot;
		angle = other.angle;
		scale = other.scale;
		verts = other.verts;
		inds = other.inds;
		verts = other.verts;
		inds = other.inds;
		mode = other.mode;
		VertexBuffer::clone(other.mVbo, mVbo);
		IndexBuffer::clone(other.mIbo, mIbo);
		mVao.bind();
		mVbo.bind();
		mIbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
		return *this;
	}

	void Polygon::render () const { IRenderable::render(); }
	void Polygon::render (const int& layer) const { IRenderable::render(layer); }
	void Polygon::render (const unsigned char& mode, const int& layer) const {
		this->mode = mode;
		IRenderable::render(layer);
	}

	void Polygon::centerPivot () {
		pivot = 0.0f;
		for (unsigned int i = 0; i < verts.size(); ++i) {
			pivot += vec2(verts[i], verts[i + 1]);
			++i;
		}
		pivot /= verts.size() / 2;
	}

	void Polygon::glRender () const {
		if (mVbo.vertCount() == verts.size() / 2)
			mVbo.setSubData(0, verts.size(), verts.data());
		else
			mVbo.setData(2, verts.size() / 2, verts.data());
		if (mIbo.indCount() == inds.size() / 2)
			mIbo.setSubData(0, inds.size(), inds.data());
		else
			mIbo.setData(inds.size(), inds.data());
		mVao.bind();
		Shader::simple().bind();
		Shader::simple().setUniform("color", color.toVec4());
		mat4 model(1.0f);
		model.translate(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		model.translate(pos);
		model.scale(scale);
		Shader::simple().setUniformMat4("model", model);
		switch (mode) {
		case KEKULE_FILL:
			if (mIbo.indCount()) {
				GL(glDrawElements(GL_TRIANGLES, mIbo.indCount(), GL_UNSIGNED_INT, 0));
			} else {
				GL(glDrawArrays(GL_TRIANGLES, 0, mVbo.vertCount()));
			}
			break;
		case KEKULE_LINE:
			if (mIbo.indCount()) {
				GL(glDrawElements(GL_TRIANGLES, mIbo.indCount(), GL_UNSIGNED_INT, 0));
			} else {
				GL(glDrawArrays(GL_LINES, 0, mVbo.vertCount()));
			}
			break;
		case KEKULE_WIREFRAME:
			GL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			if (mIbo.indCount()) {
				GL(glDrawElements(GL_TRIANGLES, mIbo.indCount(), GL_UNSIGNED_INT, 0));
			} else {
				GL(glDrawArrays(GL_TRIANGLES, 0, mVbo.vertCount()));
			}
			GL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			break;
		default:
			logError("[kekule_engine] invalid draw mode for Polygon");
		}
	}

	Circle::Circle ()
		:radius(0.0f)
		,details(0)
		,pos(0.0f)
		,pivot(0.0f)
		,scale(1.0f)
		,angle(0.0f)
		,color(0)
		,lineWidth(1.0f)
		,mode(KEKULE_FILL) {}
	
	Circle::Circle (const vec2& pos, const float& radius, const Color& c, const uint& details)
		:radius(radius)
		,details(details)
		,pos(pos)
		,pivot(pos)
		,scale(1.0f)
		,angle(0.0f)
		,color(c)
		,lineWidth(1.0f)
		,mode(KEKULE_FILL)
	{
		genVerts();
	}

	Circle::Circle (const Circle& other)
		:radius(other.radius)
		,details(other.details)
		,pos(other.pos)
		,pivot(other.pivot)
		,scale(other.scale)
		,angle(other.angle)
		,color(other.color)
		,lineWidth(1.0f)
		,mode(other.mode)
	{
		VertexBuffer::clone(other.mVbo, mVbo);
		mVao.bind();
		mVbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
	}
	
	Circle::~Circle() {}

	Circle& Circle::operator= (const Circle& other) {
		VertexBuffer::clone(other.mVbo, mVbo);
		radius = other.radius;
		details = other.details;
		pos = other.pos;
		pivot = other.pivot;
		scale = other.scale;
		angle = other.angle;
		color = other.color;
		lineWidth = other.lineWidth;
		mode = other.mode;
		mVao.bind();
		mVbo.bind();
		mVao.specifyLayout(0, 2, 2, 0);
		return *this;
	}

	void Circle::centerPivot () {
		pivot = pos;
	}

	void Circle::render () const {
		IRenderable::render();
	}

	void Circle::render (const int& layer) const {
		IRenderable::render(layer);
	}

	void Circle::render (const unsigned char& mode, const int& layer) const {
		this->mode = mode;
		IRenderable::render(layer);
	}

	void Circle::glRender () const {
		if (details + 1 != mVbo.vertCount())
			genVerts();
		mVao.bind();
		Shader::simple().bind();
		mat4 model(1.0f);
		model.translate(pivot);
		model.rotate(angle);
		model.translate(-pivot);
		model.translate(pos);
		model.scale(scale * radius);
		Shader::simple().setUniform("color", color.toVec4());
		Shader::simple().setUniformMat4("model", model);
		switch (mode) {
		case KEKULE_FILL:
			GL(glDrawArrays(GL_TRIANGLE_FAN, 0, mVbo.vertCount()));
			break;
		case KEKULE_LINE:
			GL(glLineWidth(lineWidth));
			GL(glDrawArrays(GL_LINE_STRIP, 1, mVbo.vertCount() - 1));
			GL(glLineWidth(1.0f));
			break;
		}
	}

	void Circle::genVerts () const {
		vec2* vertices = new vec2[details + 2];
		vertices[0] = 0.0f;
		for (uint i = 0; i < details; ++i) {
			vec2 p = { cosf(2 * i * PI / details), sinf(2 * i * PI / details) };
			vertices[i + 1] = { cosf(2 * i * PI / details), sinf(2 * i * PI / details) };
		}
		vertices[details + 1] = vertices[1];	//make sure that first and last vertices have same position
		mVao.bind();
		mVbo.setData(2, details + 2, (const float*)vertices);
		mVao.specifyLayout(0, 2, 2, 0);
		delete[] vertices;
	}

}
