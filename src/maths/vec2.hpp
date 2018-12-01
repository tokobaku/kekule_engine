#pragma once

#include <sstream>

namespace kekule {

	template <typename T>
	inline vector2<T>::vector2 () {}

	template <typename T>
	inline vector2<T>::vector2 (const T& scalar)
		:x(scalar), y(scalar) {}

	template <typename T>
	inline vector2<T>::vector2 (const T& x, const T& y)
		:x(x), y(y) {}

	template <typename T>
	inline vector2<T>::vector2 (const vector2<T>& other)
		:x(other.x), y(other.y) {}

	template <typename T>
	inline vector2<T>::~vector2 () {}

	template<typename T>
	template<typename N>
	inline vector2<T>::operator vector2<N> () const {
		return vector2<N>((N)x, (N)y);
	}

	template <typename T>
	template <typename N>
	inline vector2<T>::operator vector3<N> () const {
		return vector3<N>((N)x, (N)y, (N)0);
	}

	template <typename T>
	template <typename N>
	inline vector2<T>::operator vector4<N> () const {
		return vector4<N> ((N)x, (N)y, (N)0, (N)0);
	}
	
	template <typename T>
	inline vector2<T>::operator std::string () const {
		std::stringstream ss;
		ss << "vec2(" << x << ", " << y << ")";
		return ss.str();
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator+ (const vector2<T>& other) const {
		vector2<T> result = *this;
		return result += other;
	}

	template <typename T>
	inline vector2<T>& vector2<T>::operator+= (const vector2<T>& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator+ (const T& scalar) const {
		vector2<T> result = *this;
		return result += scalar;
	}

	template <typename T>
	inline vector2<T>& vector2<T>::operator+= (const T& scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator- (const vector2<T>& other) const {
		vector2<T> result = *this;
		return result -= other;
	}

	template <typename T>
	inline vector2<T>& vector2<T>::operator-= (const vector2<T>& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator- (const T& scalar) const {
		vector2<T> result = *this;
		return result -= scalar;
	}

	template <typename T>
	inline vector2<T>& vector2<T>::operator-= (const T& scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator* (const vector2<T>& other) const {
		vector2<T> result = *this;
		return result *= other;
	}

	template <typename T>
	inline vector2<T>& vector2<T>::operator*= (const vector2<T>& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator* (const T& scalar) const {
		vector2<T> result = *this;
		return result *= scalar;
	}

	template <typename T>
	inline vector2<T>& vector2<T>::operator*= (const T& scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator/ (const vector2<T>& other) const {
		vector2<T> result = *this;
		return result /= other;
	}

	template <typename T>
	inline vector2<T>& vector2<T>::operator/= (const vector2<T>& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator/ (const T& scalar) const {
		vector2<T> result = *this;
		return result /= scalar;
	}

	template <typename T>
	inline vector2<T>& vector2<T>::operator/= (const T& scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	template <typename T>
	inline T& vector2<T>::operator[] (const unsigned int& index) {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T vector2<T>::operator[] (const unsigned int& index) const {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T& vector2<T>::at (const unsigned int& index) {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T vector2<T>::at (const unsigned int& index) const {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline vector2<T> vector2<T>::operator- () const {
		return vector2<T>(-x, -y);
	}

	template <typename T>
	inline bool vector2<T>::operator== (const vector2<T>& other) const {
		return x == other.x && y == other.y;
	}

	template <typename T>
	inline bool vector2<T>::operator!= (const vector2<T>& other) const {
		return !(*this == other);
	}

	template <typename T>
	inline vector2<T>& vector2<T>::normalize () {
		return *this /= length();
	}

	template <typename T>
	inline vector2<T> vector2<T>::normalized () const {
		vector2<T> result = *this;
		return result.normalize();
	}

	template <typename T>
	inline T vector2<T>::length () const {
		return sqrt(x * x + y * y);
	}

	template <typename T>
	inline T vector2<T>::sqlength () const {
		return x * x + y * y;
	}

	template <typename T>
	inline T vector2<T>::magnitude () const {
		return length();
	}

	template <typename T>
	inline T vector2<T>::sqmagnitude () const {
		return sqlength;
	}

	template <typename T>
	vector2<T> vector2<T>::perpendicular () const {
		return vector2<T>(-y, x);
	}

	template <typename T>
	vector2<T> vector2<T>::normal () const {
		return perpendicular().normalize();
	}

	template <typename T>
	inline T vector2<T>::operator^ (const vector2<T>& other) const {
		return acos(dot(other) / (length() * other.length()));
	}

	template <typename T>
	inline T vector2<T>::angle (const vector2<T>& other) const {
		return *this ^ other;
	}

	template <typename T>
	inline T vector2<T>::dot (const vector2<T>& other) const {
		return x * other.x + y * other.y;
	}

	template <typename T>
	inline T vector2<T>::sum () const {
		return x + y;
	}

	template <typename T>
	inline T vector2<T>::product () const {
		return x * y;
	}

	template<typename T>
	inline void vector2<T>::print (std::ostream& os) const {
		os << *this << '\n';
	}

	template<typename T>
	std::ostream& operator<< (std::ostream& os, const vector2<T>& v) {
		os << "vec2(" << v.x << ", " << v.y << ")";
		return os;
	}

}