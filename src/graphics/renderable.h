#pragma once

#include "buffer_objects.h"

#define KEKULE_FILL			0
#define KEKULE_LINE			1
#define KEKULE_WIREFRAME	3

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