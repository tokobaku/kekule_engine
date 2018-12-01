#pragma once

namespace kekule {

	template <typename T>
	struct vector3;

	template <typename T>
	struct vector4;

	template <typename T>
	struct vector2 {
		union {
			struct { T x, y; };
			struct { T r, g; };
			struct { T s, t; };
		};

		vector2<T> ();
		vector2<T> (const T& scalar);
		vector2<T> (const T& x, const T& y);
		vector2<T> (const vector2<T>& other);
		~vector2<T> ();

		template <typename N>
		operator vector2<N> () const;

		template <typename N>
		operator vector3<N> () const;

		template <typename N>
		operator vector4<N> () const;

		operator std::string () const;

		vector2<T> operator+ (const vector2<T>& other) const;
		vector2<T>& operator+= (const vector2<T>& other);
		vector2<T> operator+ (const T& scalar) const;
		vector2<T>& operator+= (const T& scalar);

		vector2<T> operator- (const vector2<T>& other) const;
		vector2<T>& operator-= (const vector2<T>& other);
		vector2<T> operator- (const T& scalar) const;
		vector2<T>& operator-= (const T& scalar);

		vector2<T> operator* (const vector2<T>& other) const;
		vector2<T>& operator*= (const vector2<T>& other);
		vector2<T> operator* (const T& scalar) const;
		vector2<T>& operator*= (const T& scalar);

		vector2<T> operator/ (const vector2<T>& other) const;
		vector2<T>& operator/= (const vector2<T>& other);
		vector2<T> operator/ (const T& scalar) const;
		vector2<T>& operator/= (const T& scalar);

		T& operator[] (const unsigned int& index);
		T operator[] (const unsigned int& index) const;
		T& at (const unsigned int& index);
		T at (const unsigned int& index) const;

		vector2<T> operator- () const;

		bool operator== (const vector2<T>& other) const;
		bool operator!= (const vector2<T>& other) const;

		vector2<T>& normalize ();
		vector2<T> normalized () const;

		T length () const;
		T sqlength () const;
		T magnitude () const;
		T sqmagnitude () const;

		vector2<T> perpendicular () const;
		vector2<T> normal () const;

		//return the angle between this and other vector
		T operator^ (const vector2<T>& other) const;

		T angle (const vector2<T>& other) const;

		T dot (const vector2<T>& other) const;

		//return sum of x and y components
		T sum () const;
		//return product of x and y components
		T product () const;

		void print (std::ostream& os = std::cout) const;
	};

	template <typename T>
	std::ostream& operator<< (std::ostream& os, const vector2<T>& v);

	typedef vector2<bool>			bvec2;
	typedef vector2<double>			dvec2;
	typedef vector2<float>			vec2;
	typedef vector2<int>			ivec2;
	typedef vector2<unsigned int>	uvec2;
	typedef vector2<short>			svec2;
	typedef vector2<unsigned short> usvec2;
	typedef vector2<char>			cvec2;
	typedef vector2<unsigned char>	ucvec2;

}
#include "vec2.hpp"