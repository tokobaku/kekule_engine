#pragma once

#include "buffer_objects.h"
#include "../maths/kmath.h"
#include "renderable.h"

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
		float angle;
		
		Line ();
		Line (const vec2& head, const vec2& tail, const Color& color = Color(255));
		Line (const Line& other);
		virtual ~Line ();

		Line& operator= (const Line& other);
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
	
}