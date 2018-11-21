#pragma once

#include "buffer_objects.h"
#include "../maths/kmath.h"
#include "renderable.h"

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
		
		Line ();
		Line (const vec2& head, const vec2& tail, const Color& color = Color(255));
		Line (const Line& other);
		virtual ~Line ();
	};

	class Triangle : public IRenderable {
	protected:
		void glRender () const override;

		mutable VertexBuffer mVbo;
		mutable VertexArray mVao;
	public:
		vec2 pos1, pos2, pos3;
		Color color;
		mutable unsigned char mode;		//KEKULE_FILL, KEKULE_LINE, KEKULE_WIREFRAME

		Triangle ();
		Triangle (const vec2& pos1, const vec2& pos2, const vec2& pos3, const Color& color = Color(255));
		Triangle (const Triangle& other);
		~Triangle ();

		void render () const;
		void render (const int& layer) const;
		void render (const unsigned char& mode, const int& layer) const;
	};
	
}