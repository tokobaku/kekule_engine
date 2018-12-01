#pragma once

namespace kekule {

	template <typename T>
	inline vector4<T>::vector4 () {}

	template <typename T>
	inline vector4<T>::vector4 (const T& scalar)
		:x(scalar), y(scalar), z(scalar), w(scalar) {}

	template <typename T>
	inline vector4<T>::vector4 (const T& x, const T& y, const T& z, const T& w)
		:x(x), y(y), z(z), w(w) {}

	template <typename T>
	inline vector4<T>::vector4 (const vector2<T>& other, const T& z, const T& w)
		:x(other.x), y(other.y), z(z), w(w) {}

	template <typename T>
	inline vector4<T>::vector4 (const vector3<T>& other, const T& w)
		:x(other.x), y (other.y), z(other.z), w(w) {}

	template <typename T>
	inline vector4<T>::vector4 (const vector4<T>& other)
		:x(other.x), y(other.y), z(other.z), w(other.w) {}

	template <typename T>
	inline vector4<T>::~vector4 () {}

	template<typename T>
	template<typename N>
	inline vector4<T>::operator vector2<N> () const {
		return vector2<N>((N)x, (N)y);
	}

	template <typename T>
	template <typename N>
	inline vector4<T>::operator vector3<N> () const {
		return vector3<N>((N)x, (N)y, (N)z);
	}

	template <typename T>
	template <typename N>
	inline vector4<T>::operator vector4<N> () const {
		return vector4<N> ((N)x, (N)y, (N)z, (N)w);
	}

	template <typename T>
	inline vector4<T>::operator std::string () const {
		std::stringstream ss;
		ss << "vec2(" << x << ", " << y << ", " << z << ", " << w << ")";
		return ss.str();
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator+ (const vector4<T>& other) const {
		vector4<T> result = *this;
		return result += other;
	}

	template <typename T>
	inline vector4<T>& vector4<T>::operator+= (const vector4<T>& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator+ (const T& scalar) const {
		vector4<T> result = *this;
		return result += scalar;
	}

	template <typename T>
	inline vector4<T>& vector4<T>::operator+= (const T& scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator- (const vector4<T>& other) const {
		vector4<T> result = *this;
		return result -= other;
	}

	template <typename T>
	inline vector4<T>& vector4<T>::operator-= (const vector4<T>& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator- (const T& scalar) const {
		vector4<T> result = *this;
		return result -= scalar;
	}

	template <typename T>
	inline vector4<T>& vector4<T>::operator-= (const T& scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator* (const vector4<T>& other) const {
		vector4<T> result = *this;
		return result *= other;
	}

	template <typename T>
	inline vector4<T>& vector4<T>::operator*= (const vector4<T>& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator* (const T& scalar) const {
		vector4<T> result = *this;
		return result *= scalar;
	}

	template <typename T>
	inline vector4<T>& vector4<T>::operator*= (const T& scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator/ (const vector4<T>& other) const {
		vector4<T> result = *this;
		return result /= other;
	}

	template <typename T>
	inline vector4<T>& vector4<T>::operator/= (const vector4<T>& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator/ (const T& scalar) const {
		vector4<T> result = *this;
		return result /= scalar;
	}

	template <typename T>
	inline vector4<T>& vector4<T>::operator/= (const T& scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}

	template <typename T>
	inline T& vector4<T>::operator[] (const unsigned int& index) {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T vector4<T>::operator[] (const unsigned int& index) const {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T& vector4<T>::at (const unsigned int& index) {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline T vector4<T>::at (const unsigned int& index) const {
		return ((T*)(this))[index];
	}

	template <typename T>
	inline vector4<T> vector4<T>::operator- () const {
		return vector4<T>(-x, -y, -z, -w);
	}

	template <typename T>
	inline bool vector4<T>::operator== (const vector4<T>& other) const {
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	template <typename T>
	inline bool vector4<T>::operator!= (const vector4<T>& other) const {
		return !(*this == other);
	}

	template <typename T>
	inline vector4<T>& vector4<T>::normalize () {
		return *this /= length();
	}

	template <typename T>
	inline vector4<T> vector4<T>::normalized () const {
		vector4<T> result = *this;
		return result.normalize();
	}

	template <typename T>
	inline T vector4<T>::length () const {
		return sqrt(x * x + y * y + z * z + w * w);
	}

	template <typename T>
	inline T vector4<T>::sqlength () const {
		return x * x + y * y + z * z + w * w;
	}

	template <typename T>
	inline T vector4<T>::magnitude () const {
		return length();
	}

	template <typename T>
	inline T vector4<T>::sqmagnitude () const {
		return sqlength();
	}

	template <typename T>
	vector4<T> vector4<T>::perpendicular () const {
		return vector4<T>(-y, x, 0, 0);
	}

	template <typename T>
	vector4<T> vector4<T>::normal () const {
		return perpendicular().normalize();
	}

	template <typename T>
	inline T vector4<T>::operator^ (const vector4<T>& other) const {
		return acos(dot(other) / (length() * other.length()));
	}

	template <typename T>
	inline T vector4<T>::angle (const vector4<T>& other) const {
		return *this ^ other;
	}

	template <typename T>
	inline T vector4<T>::dot (const vector4<T>& other) const {
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	template <typename T>
	inline T vector4<T>::sum () const {
		return x + y + z + w;
	}

	template <typename T>
	inline T vector4<T>::product () const {
		return x * y * z * w;
	}

	template<typename T>
	inline void vector4<T>::print (std::ostream& os) const {
		os << *this << '\n';
	}

	template<typename T>
	std::ostream& operator<< (std::ostream& os, const vector4<T>& v) {
		os << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		return os;
	}
	
}