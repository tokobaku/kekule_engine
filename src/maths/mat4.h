#pragma once

#define MAT4_ELEMENT_COUNT	16
#define MAT4_DIMENSION		4

#include "kmath.h"

namespace kekule {

	struct mat4 {
		union {
			float elements[MAT4_ELEMENT_COUNT];
			vec4 columns[MAT4_DIMENSION];
		};

		mat4 ();
		mat4 (const float& diagonal);
		mat4 (const void* data);
		mat4 (const mat4& other);
		~mat4 ();

		mat4& operator+= (const mat4& other);
		mat4 operator+ (const mat4& other) const;
		mat4& operator+= (const float& scalar);
		mat4 operator+ (const float& scalar) const;

		mat4& operator-= (const mat4& other);
		mat4 operator- (const mat4& other) const;
		mat4& operator-= (const float& scalar);
		mat4 operator- (const float& scalar) const;

		mat4& operator*= (const mat4& other);
		mat4 operator* (const mat4& other) const;
		mat4& operator*= (const float& scalar);
		mat4 operator* (const float& scalar) const;

		mat4& operator/= (const mat4& other);
		mat4 operator/ (const mat4& other) const;
		mat4& operator/= (const float& scalar);
		mat4 operator/ (const float& scalar) const;

		mat4 operator- () const;

		bool operator== (const mat4& other) const;
		bool operator!= (const mat4& other) const;

		mat4& inverse ();
		mat4 inversed () const;

		static mat4 ortho (float left, float right, float top, float bot, float zNear, float zFar);
		static mat4 translation (const vec2& p);
		static mat4 rotation (const float& angle);
		static mat4 scalation (const vec2& s);

		mat4& translate (const vec2& p);
		mat4& rotate (const float& angle);
		mat4& scale (const vec2& s);

		/* getters and setters */
		vec4 row (const int& index) const;

		void setRow (const vec4& row, const int& index);

		vec4& operator[] (const int& index);
		vec4 operator[] (const int& index) const;
	};
	
}
#include "mat4.hpp"