#pragma once

#include "../window/utils.h"

namespace kekule {

	class VertexBuffer {
	public:
		class vertex_buffer {
		public:
			uint id, vertSize, vertCount;
			int refCount;

			vertex_buffer ();
			vertex_buffer (const uint& vertSize, const uint& vertCount, const float* data);
			vertex_buffer (const uint& vertSize, std::initializer_list<float> data);
			~vertex_buffer ();
		};
		
		mutable vertex_buffer* mRef;

		void removeRef () const;
	public:
		VertexBuffer ();
		VertexBuffer (const uint& vertSize, const uint& vertCount, const float* data);
		VertexBuffer (const uint& vertSize, std::initializer_list<float> data);
		VertexBuffer (const nullptr_t& ptr);
		VertexBuffer (const VertexBuffer& other);
		~VertexBuffer ();

		VertexBuffer& operator= (const VertexBuffer& other);
		VertexBuffer& operator= (const nullptr_t& ptr);

		bool operator== (const VertexBuffer& other) const;
		bool operator== (const nullptr_t& ptr) const;
		bool operator!= (const VertexBuffer& other) const;
		bool operator!= (const nullptr_t& ptr) const;

		operator bool () const;

		void bind () const;
		void unbind () const;
		void setData (const uint& vertSize, const uint& vertCount, const float* data);
		void setData (const uint& vertSize, std::initializer_list<float> data);
		void setSubData (const uint& offset, const uint& count, const float* data);
		void setSubData (const uint& offset, std::initializer_list<float> data);
		uint vertSize () const;
		uint vertCount () const;
		VertexBuffer clone () const;
	};

	class IndexBuffer {
	private:
		class index_buffer {
		public:
			uint id, indCount;
			int refCount;

			index_buffer ();
			index_buffer (const uint& indCount, const uint* data);
			index_buffer (std::initializer_list<uint> data);
			~index_buffer ();
		};

		void removeRef () const;
	public:
		mutable index_buffer* mRef;
		IndexBuffer ();
		IndexBuffer (const uint& indCount, const uint* data);
		IndexBuffer (std::initializer_list<uint> data);
		IndexBuffer (const nullptr_t& ptr);
		IndexBuffer (const IndexBuffer& other);
		~IndexBuffer ();

		IndexBuffer& operator= (const IndexBuffer& other);
		IndexBuffer& operator= (const nullptr_t& ptr);

		bool operator== (const IndexBuffer& other) const;
		bool operator== (const nullptr_t& other) const;
		bool operator!= (const IndexBuffer& other) const;
		bool operator!= (const nullptr_t& ptr) const;

		operator bool () const;

		void bind () const;
		void unbind () const;
		void setData (const uint& indCount, const uint* data);
		void setData (std::initializer_list<uint> data);
		void setSubData (const uint& offset, const uint& indCount, const uint* data);
		void setSubData (const uint& offset, std::initializer_list<uint> data);
		uint indCount () const;
		IndexBuffer clone () const;
	};

	class VertexArray {
	public:
		class vertex_array {
		public:
			uint id;
			int refCount;
			
			vertex_array ();
			~vertex_array ();
		};

		void removeRef () const;
		mutable vertex_array* mRef;
	public:
		VertexArray ();
		VertexArray (const VertexArray& other);
		VertexArray (const nullptr_t& ptr);
		~VertexArray ();

		VertexArray& operator= (const VertexArray& other);
		VertexArray& operator= (const nullptr_t& ptr);

		bool operator== (const VertexArray& other) const;
		bool operator== (const nullptr_t& ptr) const;
		bool operator!= (const VertexArray& other) const;
		bool operator!= (const nullptr_t& ptr) const;

		operator bool () const;

		void bind () const;
		void unbind () const;
		void specifyLayout (const int& index, const int& size, const int& stride, const int& offset) const;
	};
	
}