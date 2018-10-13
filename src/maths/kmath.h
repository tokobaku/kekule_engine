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

	template <typename T, typename N>
	T lerp (const T& a, const T& b, const N& scalar) {
		return a + (b - a) * scalar;
	}

	template <typename T, typename N>
	T smooth (const T& a, const T& b, const N& scalar) {
		return a + (b - a) * scalar * scalar * (3 - 2 * scalar);
	}

	template <typename T>
	T dot (const vector2<T>& u, const vector2<T>& v) {
		return u.dot(v);
	}

	template <typename T>
	T dot (const vector3<T>& u, const vector3<T>& v) {
		return u.dot(v);
	}

	template <typename T>
	vector3<T> cross (const vector3<T>& u, const vector3<T>& v) {
		return u.cross(v);
	}

	template <typename T>
	float length (const vector2<T>& v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	template <typename T>
	float sqlength (const vector2<T>& v) {
		return v.x * v.x + v.y * v.y;
	}

}