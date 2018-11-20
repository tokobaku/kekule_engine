#include "shader.h"
#include "renderable.h"

namespace kekule {

	void IRenderable::glRender () const {}

	IRenderable::IRenderable () :layer(0) {}
	IRenderable::IRenderable (const int& layer) :layer(layer) {}
	IRenderable::~IRenderable () {}
	
}