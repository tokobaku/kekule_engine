#pragma once

namespace kekule {

	template <typename T>
	struct vector4 {
		union {
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T s, t, u, v; };
		};

		vector4<T> ();
		vector4<T> (const T& scalar);
		vector4<T> (const T& x, const T& y, const T& z, const T& w);
		vector4<T> (const vector2<T>& other, const T& z = 0, const T& w = 0);
		vector4<T> (const vector3<T>& other, const T& w = 0);
		vector4<T> (const vector4<T>& other);
		~vector4<T> ();

		template <typename N>
		operator vector2<N> () const;

		template <typename N>
		operator vector3<N> () const;

		template <typename N>
		operator vector4<N> () const;

		vector4<T> operator+ (const vector4<T>& other) const;
		vector4<T>& operator+= (const vector4<T>& other);
		vector4<T> operator+ (const T& other) const;
		vector4<T>& operator+= (const T& other);

		vector4<T> operator- (const vector4<T>& other) const;
		vector4<T>& operator-= (const vector4<T>& other);
		vector4<T> operator- (const T& other) const;
		vector4<T>& operator-= (const T& other);

		vector4<T> operator* (const vector4<T>& other) const;
		vector4<T>& operator*= (const vector4<T>& other);
		vector4<T> operator* (const T& other) const;
		vector4<T>& operator*= (const T& other);

		vector4<T> operator/ (const vector4<T>& other) const;
		vector4<T>& operator/= (const vector4<T>& other);
		vector4<T> operator/ (const T& other) const;
		vector4<T>& operator/= (const T& other);

		T& operator[] (const unsigned int& index);
		T operator[] (const unsigned int& index) const;
		T& at (const unsigned int& index);
		T at (const unsigned int& index) const;

		vector4<T> operator- () const;

		bool operator== (const vector4<T>& other) const;
		bool operator!= (const vector4<T>& other) const;

		vector4<T>& normalize ();
		vector4<T> normalized () const;

		T length () const;
		T sqlength () const;
		T magnitude () const;
		T sqmagnitude () const;

		vector4<T> perpendicular () const;
		vector4<T> normal () const;

		//return angle between this and other vectors
		T operator^ (const vector4<T>& other) const;
		T angle (const vector4<T>& other) const;

		T dot (const vector4<T>& other) const;

		T sum () const;
		T product () const;

		void print (std::ostream& os = std::cout) const;
	};

	template <typename T>
	std::ostream& operator<< (std::ostream& os, const vector4<T>& v);

	typedef vector4<bool>			bvec4;
	typedef vector4<double>			dvec4;
	typedef vector4<float>			vec4;
	typedef vector4<int>			ivec4;
	typedef vector4<unsigned int>	uvec4;
	typedef vector4<short>			svec4;
	typedef vector4<unsigned short> usvec4;
	typedef vector4<char>			cvec4;
	typedef vector4<unsigned char>	ucvec4;

	struct Color : public ucvec4 {
		inline Color () : ucvec4() {}
		inline Color (const unsigned char& rgb, const unsigned char& a = 255) : ucvec4(rgb, rgb, rgb, a) {}
		inline Color (const unsigned char& r, const unsigned char& g, const unsigned char& b
					,const unsigned char& a = 255) : ucvec4(r, g, b, a) {}
		inline Color (const Color& other) : ucvec4(other.r, other.g, other.b, other.a) {}

		inline vec4 toVec4 () const { return vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }
	};

}

#include "vec4.hpp"