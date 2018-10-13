#pragma once

#include <iostream>
#include <cstring>

#define MAT4_DIMENSION		4
#define MAT4_ELEMENT_COUNT	16

namespace kekule {

	struct mat4 {
		union {
			float elements[MAT4_ELEMENT_COUNT];
			vec4 columns[MAT4_DIMENSION];
		};

		mat4 ();
		mat4 (const float& diagonal);
		mat4 (const float* elements);
		mat4 (const vec4* columns);
		mat4 (const vec4& c1, const vec4& c2, const vec4& c3, const vec4& c4);
		mat4 (const mat4& other);
		~mat4 ();

		mat4 operator+ (const mat4& other) const;
		mat4& operator+= (const mat4& other);
		mat4 operator+ (const float& scalar) const;
		mat4& operator+= (const float& scalar);

		mat4 operator- (const mat4& other) const;
		mat4& operator-= (const mat4& other);
		mat4 operator- (const float& scalar) const;
		mat4& operator-= (const float& scalar);

		mat4 operator* (const mat4& other) const;
		mat4& operator*= (const mat4& other);
		mat4 operator* (const float& scalar) const;
		mat4& operator*= (const float& scalar);

		vec4& operator[] (const unsigned int& index);

		vec4 column (const unsigned int& index) const;
		vec4 row (const unsigned int& index) const;
		float at(const unsigned int& column, const unsigned int& row) const;

		bool operator== (const mat4& other) const;
		bool operator!= (const mat4& other) const;

		mat4& scale (const vec3& axis);
		static mat4 scalation (const vec3& axis);
		mat4& translate (const vec3& v);
		static mat4 translation (const vec3& v);
		mat4& rotate (const float& angle, vec3 axis, const bool& normalized = false);
		static mat4 rotation (const float& angle, vec3 axis, const bool& normalized = false);

		static mat4 ortho (const float& left, const float& right, const float& top, const float& bottom, const float& far, const float& near);

		void setColumn (const unsigned int& index, const vec4& column);
		void setRow (const unsigned int& index, const vec4& row);

		void print (std::ostream & os = std::cout) const;
	};

	vec4 operator* (const mat4& m, const vec4& v);
	vec4 operator* (const vec4& v, const mat4& m);
	vec4& operator*= (vec4& v, const mat4& m);

	std::ostream& operator<< (std::ostream& os, const mat4& m);

}
#include "mat4.hpp"