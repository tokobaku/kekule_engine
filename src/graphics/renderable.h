#pragma once
#include "../maths/kmath.h"
#include "buffer_objects.h"

namespace kekule {

	class IRenderable {
	protected:
		virtual void glRender () const;
	public:
		IRenderable ();
		IRenderable (const int& layer);
		virtual ~IRenderable ();
		mutable int layer;

		/* TODO: add renderer
		void render () const;
		void render (const int& layer) const;
		*/
	};
	
}