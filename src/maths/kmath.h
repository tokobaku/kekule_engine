#pragma once

#include <iostream>
#define PI			3.14
#define DEG_TO_RAD 3.14 / 180.
#define RAD_TO_DEG 180.0 / 3.14

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

namespace kekule {

	template <typename T>
	inline T clamp (const T& min, const T& max, const T& value) {
		return value < min ? min : (value > max ? max : value);
	}

	template <typename T, typename N>
	inline T lerp (const T& a, const T& b, const N& scalar) {
		return a + (b - a) * scalar;
	}

	template <typename T, typename N>
	inline T smooth (const T& a, const T& b, const N& scalar) {
		return a + (b - a) * scalar * scalar * (3 - 2 * scalar);
	}

	template <typename T>
	inline T dot (const vector2<T>& u, const vector2<T>& v) {
		return u.dot(v);
	}

	template <typename T>
	inline T dot (const vector3<T>& u, const vector3<T>& v) {
		return u.dot(v);
	}

	template <typename T>
	inline vector3<T> cross (const vector3<T>& u, const vector3<T>& v) {
		return u.cross(v);
	}

	template <typename T>
	inline float length (const vector2<T>& v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	template <typename T>
	inline float sqlength (const vector2<T>& v) {
		return v.x * v.x + v.y * v.y;
	}

}