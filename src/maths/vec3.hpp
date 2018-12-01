#pragma once

#include <math.h>

namespace kekule {

	template <typename T>
	inline vector3<T>::vector3 () {}

	template <typename T>
	inline vector3<T>::vector3 (const T& scalar)
		:x(scalar), y(scalar), z(scalar) {}

	template <typename T>
	inline vector3<T>::vector3 (const T& x, const T& y, const T& z)
		:x(x), y(y), z(z) {}

	template <typename T>
	inline vector3<T>::vector3 (const vector2<T>& other, const T& z)
		:x(other.x), y(other.y), z(z) {}

	template <typename T>
	inline vector3<T>::vector3 (const vector3<T>& other)
		:x(other.x), y(other.y), z(other.z) {}

	template <typename T>
	inline vector3<T>::~vector3 () {}

	template<typename T>
	template<typename N>
	inline vector3<T>::operator vector2<N> () const {
		return vector2<N>((N)x, (N)y);
	}

	template <typename T>
	template <typename N>
	inline vector3<T>::operator vector3<N> () const {
		return vector3<N>((N)x, (N)y, (N)z);
	}

	template <typename T>
	template <typename N>
	inline vector3<T>::operator vector4<N> () const {
		return vector4<N> ((N)x, (N)y, (N)z, (N)0);
	}

	template <typename T>
	inline vector3<T>::operator std::string () const {
		std::stringstream ss;
		ss << "vec3(" << x << ", " << y << ", " << z << ")";
		return ss.str();
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator+ (const vector3<T>& other) const {
		vector3<T> result = *this;
		return result += other;
	}

	template <typename T>
	inline vector3<T>& vector3<T>::operator+= (const vector3<T>& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator+ (const T& scalar) const {
		vector3<T> result = *this;
		return result += scalar;
	}

	template <typename T>
	inline vector3<T>& vector3<T>::operator+= (const T& scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator- (const vector3<T>& other) const {
		vector3<T> result = *this;
		return result -= other;
	}

	template <typename T>
	inline vector3<T>& vector3<T>::operator-= (const vector3<T>& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator- (const T& scalar) const {
		vector3<T> result = *this;
		return result -= scalar;
	}

	template <typename T>
	inline vector3<T>& vector3<T>::operator-= (const T& scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator* (const vector3<T>& other) const {
		vector3<T> result = *this;
		return result *= other;
	}

	template <typename T>
	inline vector3<T>& vector3<T>::operator*= (const vector3<T>& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator* (const T& scalar) const {
		vector3<T> result = *this;
		return result *= scalar;
	}

	template <typename T>
	inline vector3<T>& vector3<T>::operator*= (const T& scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator/ (const vector3<T>& other) const {
		vector3<T> result = *this;
		return result /= other;
	}

	template <typename T>
	inline vector3<T>& vector3<T>::operator/= (const vector3<T>& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator/ (const T& scalar) const {
		vector3<T> result = *this;
		return result /= scalar;
	}

	template <typename T>
	inline vector3<T>& vector3<T>::operator/= (const T& scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	template <typename T>
	inline T& vector3<T>::operator[] (const unsigned int& index) {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T vector3<T>::operator[] (const unsigned int& index) const {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T& vector3<T>::at (const unsigned int& index) {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T vector3<T>::at (const unsigned int& index) const {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline vector3<T> vector3<T>::operator- () const {
		return vector3<T>(-x, -y, -z);
	}

	template <typename T>
	inline bool vector3<T>::operator== (const vector3<T>& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	template <typename T>
	inline bool vector3<T>::operator!= (const vector3<T>& other) const {
		return !(*this == other);
	}

	template <typename T>
	inline vector3<T>& vector3<T>::normalize () {
		return *this /= length();
	}

	template <typename T>
	inline vector3<T> vector3<T>::normalized () const {
		vector3<T> result = *this;
		return result.normalize();
	}

	template <typename T>
	inline T vector3<T>::length () const {
		return sqrt(x * x + y * y + z * z);
	}

	template <typename T>
	inline T vector3<T>::sqlength () const {
		return x * x + y * y + z * z;
	}

	template <typename T>
	inline T vector3<T>::magnitude () const {
		return length();
	}

	template <typename T>
	inline T vector3<T>::sqmagnitude () const {
		return sqlength();
	}

	template <typename T>
	vector3<T> vector3<T>::perpendicular () const {
		return vector3<T>(-y, x, 0);
	}

	template <typename T>
	vector3<T> vector3<T>::normal () const {
		return perpendicular().normalize();
	}

	template <typename T>
	inline T vector3<T>::operator^ (const vector3<T>& other) const {
		return acos(dot(other) / (length() * other.length()));
	}

	template <typename T>
	inline T vector3<T>::angle (const vector3<T>& other) const {
		return *this ^ other;
	}

	template <typename T>
	inline T vector3<T>::dot (const vector3<T>& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	template <typename T>
	inline vector3<T> vector3<T>::cross (const vector3<T>& other) const {
		return vector3<T> (
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
			);
	}

	template <typename T>
	inline T vector3<T>::sum () const {
		return x + y + z;
	}

	template <typename T>
	inline T vector3<T>::product () const {
		return x * y * z;
	}

	template<typename T>
	inline void vector3<T>::print (std::ostream& os) const {
		os << *this << '\n';
	}

	template<typename T>
	std::ostream& operator<< (std::ostream& os, const vector3<T>& v) {
		os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}

}