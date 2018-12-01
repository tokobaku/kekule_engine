#pragma once

namespace kekule {

	template <typename T>
	struct vector2;

	template <typename T>
	struct vector4;

	template <typename T>
	struct vector3 {
		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
			struct { T s, t, u; };
		};

		vector3<T> ();
		vector3<T> (const T& scalar);
		vector3<T> (const T& x, const T& y, const T& z);
		vector3<T> (const vector2<T>& other, const T& z = 0);
		vector3<T> (const vector3<T>& other);
		~vector3<T> ();

		template <typename N>
		operator vector2<N> () const;

		template <typename N>
		operator vector3<N> () const;

		template <typename N>
		operator vector4<N> () const;

		operator std::string () const;

		vector3<T> operator+ (const vector3<T>& other) const;
		vector3<T>& operator+= (const vector3<T>& other);
		vector3<T> operator+ (const T& other) const;
		vector3<T>& operator+= (const T& other);

		vector3<T> operator- (const vector3<T>& other) const;
		vector3<T>& operator-= (const vector3<T>& other);
		vector3<T> operator- (const T& other) const;
		vector3<T>& operator-= (const T& other);

		vector3<T> operator* (const vector3<T>& other) const;
		vector3<T>& operator*= (const vector3<T>& other);
		vector3<T> operator* (const T& other) const;
		vector3<T>& operator*= (const T& other);

		vector3<T> operator/ (const vector3<T>& other) const;
		vector3<T>& operator/= (const vector3<T>& other);
		vector3<T> operator/ (const T& other) const;
		vector3<T>& operator/= (const T& other);

		
		T& operator[] (const unsigned int& index);
		T operator[] (const unsigned int& index) const;
		T& at (const unsigned int& index);
		T at (const unsigned int& index) const;

		vector3<T> operator- () const;

		bool operator== (const vector3<T>& other) const;
		bool operator!= (const vector3<T>& other) const;

		vector3<T>& normalize ();
		vector3<T> normalized () const;

		T length () const;
		T sqlength () const;
		T magnitude () const;
		T sqmagnitude () const;

		vector3<T> perpendicular () const;
		vector3<T> normal () const;

		//return angle between this and other vectors
		T operator^ (const vector3<T>& other) const;
		T angle (const vector3<T>& other) const;

		T dot (const vector3<T>& other) const;
		vector3<T> cross (const vector3<T>& other) const;

		T sum () const;
		T product () const;

		void print (std::ostream& os = std::cout) const;
	};

	template <typename T>
	std::ostream& operator<< (std::ostream& os, const vector3<T>& v);

	typedef vector3<bool>			bvec3;
	typedef vector3<double>			dvec3;
	typedef vector3<float>			vec3;
	typedef vector3<int>			ivec3;
	typedef vector3<unsigned int>	uvec3;
	typedef vector3<short>			svec3;
	typedef vector3<unsigned short> usvec3;
	typedef vector3<char>			cvec3;
	typedef vector3<unsigned char>	ucvec3;

}

#include "vec3.hpp"