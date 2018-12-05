#pragma once

#include "buffer_objects.h"

namespace kekule {

	class IRenderable {
		friend class Renderer;
	protected:
		virtual void glRender () const;
	public:
		mutable int layer;
		
		IRenderable ();
		IRenderable (const int& layer);
		virtual ~IRenderable ();

		void render () const;
		void render (const int& layer) const;
	};
	
}