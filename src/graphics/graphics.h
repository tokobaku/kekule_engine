#pragma once

#include "buffer_objects.h"
#include "../maths/kmath.h"
#include "renderable.h"
#include <vector>

#define KEKULE_FILL			0
#define KEKULE_LINE 		1
#define KEKULE_WIREFRAME	2

namespace kekule {

	class Line : public IRenderable {
	protected:
		void glRender () const override;

		mutable VertexBuffer mVbo;
		mutable VertexArray mVao;

	public:
		vec2 head, tail;
		Color color;
		float width;
		vec2 pivot;
		vec2 scale;
		float angle;
		
		Line ();
		Line (const vec2& head, const vec2& tail, const Color& color = Color(255));
		Line (const Line& other);
		virtual ~Line ();

		Line& operator= (const Line& other);
	};

	class PolyLine : public IRenderable {
	protected:
		void glRender () const override;

		mutable VertexBuffer mVbo;
		mutable VertexArray mVao;
	public:
		std::vector<vec2> verts;
		vec2 pos;
		vec2 scale;
		vec2 pivot;
		Color color;
		float angle;
		float width;

		PolyLine ();
		PolyLine (const std::vector<float>& verts, const Color& color = Color(255));
		PolyLine (const PolyLine& other);
		~PolyLine ();

		PolyLine& operator= (const PolyLine& other);
		
		void centerPivot ();
	};

	class Triangle : public IRenderable {
	protected:
		void glRender () const override;

		mutable VertexBuffer mVbo;
		mutable VertexArray mVao;
	public:
		vec2 p1, p2, p3;
		Color color;
		mutable unsigned char mode;		//KEKULE_FILL, KEKULE_LINE, KEKULE_WIREFRAME
		vec2 pivot;
		vec2 scale;
		vec2 pos;
		float angle;

		Triangle ();
		Triangle (const vec2& pos1, const vec2& pos2, const vec2& pos3, const Color& color = Color(255));
		Triangle (const Triangle& other);
		~Triangle ();

		Triangle& operator= (const Triangle& other);

		void render () const;
		void render (const int& layer) const;
		void render (const unsigned char& mode, const int& layer) const;
	};

	class Rect : public IRenderable {
	protected:
		void glRender () const override;

		static VertexBuffer mVbo;
		static VertexArray mVao;
	public:
		vec2 pos;
		float width, height;
		Color color;
		mutable unsigned char mode;
		vec2 pivot;
		float angle;

		Rect ();
		Rect (const vec2& pos, const float& width, const float& height, const Color& c = Color(255));
		Rect (const Rect& other);
		~Rect ();

		Rect& operator= (const Rect& other);

		void render () const;
		void render (const int& layer) const;
		void render (const unsigned char& mode, const int& layer) const;
	};

	//TODO: Allow user to pass gl draw modes (like GL_TRIANGLES, GL_LINES, etc.)
	class Polygon : public IRenderable {
	protected:
		void glRender () const override;

		mutable VertexBuffer mVbo;
		mutable IndexBuffer mIbo;
		mutable VertexArray mVao;
	public:
		Color color;
		vec2 pos;
		vec2 pivot;
		float angle;
		vec2 scale;
		std::vector<float> verts;
		std::vector<uint> inds;
		mutable unsigned char mode;
	
		Polygon ();
		Polygon (std::initializer_list<float> verts, std::initializer_list<uint> inds = {}, const Color& c = Color(255));
		Polygon (const uint& vertCount, const float* vertData, const uint& indCount = 0, const uint* indData = nullptr, const Color& c = Color(255));
		Polygon (const Polygon& other);
		~Polygon ();

		Polygon& operator= (const Polygon& other);

		void render () const;
		void render (const int& layer) const;
		void render (const unsigned char& mode, const int& layer) const;

		void centerPivot ();
	};

	class Circle : public IRenderable {
	protected:
		void glRender () const override;
	
		mutable VertexBuffer mVbo;
		mutable VertexArray mVao;

		void genVerts () const;
	public:
		float radius;
		uint details;
		vec2 pos;
		vec2 pivot;
		vec2 scale;
		float angle;
		Color color;
		float lineWidth;
		mutable unsigned char mode;

		Circle ();
		Circle (const vec2& pos, const float& radius, const Color& c = Color(255), const uint& details = 20);
		Circle (const Circle& other);
		~Circle();

		Circle& operator= (const Circle& other);

		void centerPivot ();

		void render () const;
		void render (const int& layer) const;
		void render (const unsigned char& mode, const int& layer) const;
	};
	
}