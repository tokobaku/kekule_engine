#include "buffer_objects.h"

namespace kekule {

	VertexBuffer::vertex_buffer::vertex_buffer ()
		:id(0), vertSize(0), vertCount(0), refCount(1) {}

	VertexBuffer::vertex_buffer::vertex_buffer (const uint& vertSize, const uint& vertCount, const float* data)
		:id(0), vertSize(vertSize), vertCount(vertCount), refCount(1)
	{
		GL(glGenBuffers(1, &id));
		GL(glBindBuffer(GL_ARRAY_BUFFER, id));
		GL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertSize * vertCount, data, GL_STATIC_DRAW));
	}

	VertexBuffer::vertex_buffer::vertex_buffer (const uint& vertSize, std::initializer_list<float> data)
		:id(0), vertSize(vertSize), vertCount(data.size() / vertSize), refCount(1)
	{
		GL(glGenBuffers(1, &id));
		GL(glBindBuffer(GL_ARRAY_BUFFER, id));
		GL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertSize * vertCount, data.begin(), GL_STATIC_DRAW));
	}

	VertexBuffer::vertex_buffer::~vertex_buffer () {
		if (this->id) {
			GL(glDeleteBuffers(1, &id));
		}
	}

	VertexBuffer::VertexBuffer ()
		:mRef(nullptr) {}
	
	VertexBuffer::VertexBuffer (const uint& vertSize, const uint& vertCount, const float* data)
		:mRef(new vertex_buffer(vertSize, vertCount, data)) {}
	
	VertexBuffer::VertexBuffer (const uint& vertSize, std::initializer_list<float> data)
		:mRef(new vertex_buffer(vertSize, data)) {}
	
	VertexBuffer::VertexBuffer (const nullptr_t& ptr) {
		removeRef();
		mRef = ptr;
	}
	
	VertexBuffer::VertexBuffer (const VertexBuffer& other) {
		removeRef();
		if (other.mRef != nullptr) {
			other.mRef->refCount++;
			mRef = other.mRef;
		}
	}

	VertexBuffer::~VertexBuffer () {
		removeRef();
	}

	void VertexBuffer::removeRef () const {
		if (mRef != nullptr) {
			mRef->refCount--;
			if (mRef->refCount < 1)
				delete mRef;
		}
	}

	VertexBuffer& VertexBuffer::operator= (const VertexBuffer& other) {
		removeRef();
		mRef = other.mRef;
		if (mRef != nullptr)
			mRef->refCount++;
		return *this;
	}

	VertexBuffer& VertexBuffer::operator= (const nullptr_t& ptr) {
		removeRef();
		mRef = ptr;
		return *this;
	}

	bool VertexBuffer::operator== (const VertexBuffer& other) const { return mRef == other.mRef; }
	bool VertexBuffer::operator== (const nullptr_t& ptr) const { return mRef == ptr; }
	bool VertexBuffer::operator!= (const VertexBuffer& other) const { return mRef != other.mRef; }
	bool VertexBuffer::operator!= (const nullptr_t& ptr) const { return mRef != ptr; }

	VertexBuffer::operator bool () const { return mRef != nullptr; }

	void VertexBuffer::bind () const { GL(glBindBuffer(GL_ARRAY_BUFFER, mRef == nullptr ? 0 : mRef->id)); }
	void VertexBuffer::unbind () const { GL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
	
	void VertexBuffer::setData (const uint& vertSize, const uint& vertCount, const float* data) {
		if (mRef == nullptr) {
			mRef = new vertex_buffer(vertSize, vertCount, data);
			return;
		}
		
		GL(glBindBuffer(GL_ARRAY_BUFFER, mRef->id));
		GL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertSize * vertCount, data, GL_STATIC_DRAW));
		mRef->vertSize = vertSize;
		mRef->vertCount = vertCount;
	}

	void VertexBuffer::setData (const uint& vertSize, std::initializer_list<float> data) {
		this->setData(vertSize, data.size() / vertSize, data.begin());
	}

	void VertexBuffer::setSubData (const uint& offset, const uint& vertCount, const float* data) {
		if (mRef == nullptr) {
			logError("Calling VertexBuffer::setSubData() for uninitialized instance");
			return;
		}
		GL(glBindBuffer(GL_ARRAY_BUFFER, mRef->id));
		GL(glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float) * mRef->vertSize,
						vertCount * sizeof(float) * mRef->vertSize, data));
	}

	void VertexBuffer::setSubData (const uint& offset, std::initializer_list<float> data) {
		this->setSubData(offset, data.size() / mRef->vertSize, data.begin());
	}

	uint VertexBuffer::vertSize () const { return mRef == nullptr ? 0 : mRef->vertSize; }
	uint VertexBuffer::vertCount () const { return mRef == nullptr ? 0 : mRef->refCount; }

	VertexBuffer VertexBuffer::clone () const {
		if (mRef == nullptr)
			return *this;
		
		VertexBuffer vbo;
		vbo.mRef = new vertex_buffer();
		glGenBuffers(1, &vbo.mRef->id);
		glBindBuffer(GL_ARRAY_BUFFER, vbo.mRef->id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mRef->refCount * mRef->vertSize, 0, GL_STATIC_DRAW);
		glBindBuffer(GL_COPY_READ_BUFFER, mRef->id);
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0, sizeof(float) * mRef->vertCount * mRef->vertSize);
		vbo.mRef->vertSize = mRef->vertSize;
		vbo.mRef->vertCount = mRef->vertCount;
		return vbo;
	}

	IndexBuffer::index_buffer::index_buffer ()
		:id(0), indCount(0), refCount(1) {}

	IndexBuffer::index_buffer::index_buffer (const uint& indCount, const uint* data)
		:id(0), indCount(indCount), refCount(1)
	{
		GL(glGenBuffers(1, &id));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
		GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indCount, data, GL_STATIC_DRAW));
	}

	IndexBuffer::index_buffer::index_buffer (std::initializer_list<uint> data)
		:id(0), indCount(data.size()), refCount(1)
	{
		GL(glGenBuffers(1, &id));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
		GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * data.size(), data.begin(), GL_STATIC_DRAW));
	}

	IndexBuffer::index_buffer::~index_buffer () {
		if (id) {
			GL(glDeleteBuffers(1, &id));
		}
	}

	void IndexBuffer::removeRef () const {
		if (mRef != nullptr) {
			mRef->refCount--;
			if (mRef->refCount < 1)
				delete mRef;
		}
	}

	IndexBuffer::IndexBuffer ()
		:mRef(nullptr) {}
	
	IndexBuffer::IndexBuffer (const uint& indCount, const uint* data)
		:mRef(new index_buffer(indCount, data)) {}
	
	IndexBuffer::IndexBuffer (std::initializer_list<uint> data)
		:mRef(new index_buffer(data)) {}
	
	IndexBuffer::IndexBuffer (const nullptr_t& ptr)
		:mRef(ptr) {}
	
	IndexBuffer::IndexBuffer (const IndexBuffer& other)
		:mRef(other.mRef)
	{
		if (other != nullptr)
			other.mRef->refCount++;
	}

	IndexBuffer::~IndexBuffer () {
		removeRef();
	}

	IndexBuffer& IndexBuffer::operator= (const IndexBuffer& other) {
		removeRef();
		mRef = other.mRef;
		if (mRef != nullptr)
			mRef->refCount++;
		return *this;
	}

	IndexBuffer& IndexBuffer::operator= (const nullptr_t& ptr) {
		removeRef();
		mRef = ptr;
		return *this;
	}

	bool IndexBuffer::operator== (const IndexBuffer& other) const { return mRef == other.mRef; }
	bool IndexBuffer::operator== (const nullptr_t& ptr) const { return mRef == ptr; }
	bool IndexBuffer::operator!= (const IndexBuffer& other) const { return mRef != other.mRef; }
	bool IndexBuffer::operator!= (const nullptr_t& ptr) const { return mRef != ptr; }

	IndexBuffer::operator bool () const { return mRef != nullptr; }

	void IndexBuffer::bind () const {
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRef == nullptr ? 0 : mRef->id));
	}

	void IndexBuffer::unbind () const {
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::setData (const uint& indCount, const uint* data) {
		if (mRef == nullptr) {
			mRef = new index_buffer(indCount, data);
			return;
		}

		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRef->id));
		GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indCount, data, GL_STATIC_DRAW));
		mRef->indCount = indCount;
	}

	void IndexBuffer::setData (std::initializer_list<uint> data) {
		this->setData(data.size(), data.begin());
	}

	void IndexBuffer::setSubData (const uint& offset, const uint& indCount, const uint* data) {
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRef->id));
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint), indCount * sizeof(uint), data);
	}

	void IndexBuffer::setSubData (const uint& offset, std::initializer_list<uint> data) {
		this->setSubData(offset, data.size(), data.begin());
	}

	uint IndexBuffer::indCount () const {
		return mRef == nullptr ? 0 : mRef->indCount;
	}

	IndexBuffer IndexBuffer::clone () const {
		if (mRef == nullptr)
			return nullptr;
		
		IndexBuffer vbo;
		vbo.mRef = new index_buffer();
		GL(glGenBuffers(1, &vbo.mRef->id));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.mRef->id));
		GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mRef->indCount, nullptr, GL_STATIC_DRAW));
		GL(glBindBuffer(GL_COPY_READ_BUFFER, mRef->id));
		GL(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ELEMENT_ARRAY_BUFFER, 0, 0, mRef->indCount * sizeof(uint)));
		return vbo;
	}

	VertexArray::vertex_array::vertex_array ()
		:id(0), refCount(1) {}
	
	VertexArray::vertex_array::~vertex_array () {
		if (id) {
			GL(glDeleteVertexArrays(1, &id));
		}
	}

	void VertexArray::removeRef () const {
		if (mRef != nullptr) {
			mRef->refCount--;
			if (mRef->refCount < 1)
				delete mRef;
		}
	}

	VertexArray::VertexArray ()
		:mRef(nullptr) {}

	VertexArray::VertexArray (const VertexArray& other)
		:mRef(other.mRef)
	{
		if (other.mRef != nullptr)
			other.mRef->refCount++;
	}

	VertexArray::VertexArray (const nullptr_t& ptr)
		:mRef(ptr) {}
	
	VertexArray::~VertexArray () {
		removeRef();
	}

	VertexArray& VertexArray::operator= (const VertexArray& other) {
		removeRef();
		mRef = other.mRef;
		if (mRef != nullptr)
			mRef->refCount++;
		return *this;
	}

	VertexArray& VertexArray::operator= (const nullptr_t& ptr) {
		removeRef();
		mRef = ptr;
		return *this;
	}

	bool VertexArray::operator== (const VertexArray& other) const { return mRef == other.mRef; }
	bool VertexArray::operator== (const nullptr_t& ptr) const { return mRef == ptr; }
	bool VertexArray::operator!= (const VertexArray& other) const { return mRef != other.mRef; }
	bool VertexArray::operator!= (const nullptr_t& ptr) const { return mRef != ptr; }
	VertexArray::operator bool () const { return mRef != nullptr; }

	void VertexArray::bind () const {
		if (mRef == nullptr) {
			mRef = new vertex_array();
			GL(glGenVertexArrays(1, &mRef->id));
		}
		GL(glBindVertexArray(mRef->id));
	}

	void VertexArray::unbind () const { GL(glBindVertexArray(0)); }

	void VertexArray::specifyLayout (const int& index, const int& size, const int& stride, const int& offset) const {
		GL(glEnableVertexAttribArray(index));
		GL(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(sizeof(float) * offset)));
	}
	
}