#include "shader.h"
#include "renderable.h"
#include "renderer.h"

namespace kekule {

	void IRenderable::glRender () const {}

	IRenderable::IRenderable () :layer(0) {}
	IRenderable::IRenderable (const int& layer) :layer(layer) {}
	IRenderable::~IRenderable () {}

	void IRenderable::render () const {
		auto iter = Renderer::mQueue.find(this->layer);
		if (iter == Renderer::mQueue.end())
			Renderer::mQueue.insert(this);
		else
			iter->queue.push_back(this);
	}

	void IRenderable::render (const int& layer) const {
		this->layer = layer;
		this->render();
	}
	
}