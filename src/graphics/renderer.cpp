#include "renderer.h"
#include "renderable.h"

namespace kekule {

	std::set<Renderer::RendererLayer> Renderer::mQueue;

	Renderer::RendererLayer::RendererLayer ()
		:queue(), layer() {}
	
	Renderer::RendererLayer::RendererLayer (const IRenderable* item)
		:queue({item}), layer(item->layer) {}
	
	Renderer::RendererLayer::RendererLayer (const int& layer)
		:queue(), layer(layer) {}
	
	Renderer::RendererLayer::~RendererLayer () {}

	bool Renderer::RendererLayer::operator< (const Renderer::RendererLayer& other) const {
		return this->layer < other.layer;
	}

	bool Renderer::RendererLayer::operator<= (const Renderer::RendererLayer& other) const {
		return this->layer <= other.layer;
	}

	bool Renderer::RendererLayer::operator> (const Renderer::RendererLayer& other) const {
		return this->layer > other.layer;
	}

	bool Renderer::RendererLayer::operator>= (const Renderer::RendererLayer& other) const {
		return this->layer >= other.layer;
	}

	bool Renderer::RendererLayer::operator== (const Renderer::RendererLayer& other) const {
		return this->layer == other.layer;
	}

	bool Renderer::RendererLayer::operator!= (const Renderer::RendererLayer& other) const {
		return this->layer != other.layer;
	}

	void Renderer::RendererLayer::render () const {
		auto first = queue.begin();
		auto last = queue.end();
		while (first != last) {
			(*first)->glRender();
			first = queue.erase(first);
		}
	}

	void Renderer::render () {
		auto first = mQueue.begin();
		auto last = mQueue.end();
		while (first != last) {
			first->render();
			first = mQueue.erase(first);
		}
	}
	
}