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
		
		Line ();
		Line (const vec2& head, const vec2& tail, const Color& color = Color(255));
		Line (const Line& other);
		virtual ~Line ();

		void render () const;
	};
	
}