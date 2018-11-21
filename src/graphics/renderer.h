#pragma once

#include <set>
#include <list>
#include "renderable.h"

namespace kekule {

	class Renderer {
		friend class IRenderable;
		friend class Window;
	private:
		class RendererLayer {
		public:
			mutable std::list<const IRenderable*> queue;
			int layer;
		
			RendererLayer ();
			RendererLayer (const IRenderable* item);
			RendererLayer (const int& layer);
			~RendererLayer ();

			bool operator< (const RendererLayer& other) const;
			bool operator<= (const RendererLayer& other) const;
			bool operator> (const RendererLayer& other) const;
			bool operator>= (const RendererLayer& other) const;
			bool operator== (const RendererLayer& other) const;
			bool operator!= (const RendererLayer& other) const;

			void render () const;
		};

		static std::set<RendererLayer> mQueue;

		static void render ();
	};
	
}