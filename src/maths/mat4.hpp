#pragma once

#include "math.h"
#include "string.h"

namespace kekule {

	inline mat4::mat4 () {}

	inline mat4::mat4 (const float& diagonal) {
		columns[0] = {diagonal, 0.0f, 0.0f, 0.0f};
		columns[1] = {0.0f, diagonal, 0.0f, 0.0f};
		columns[2] = {0.0f, 0.0f, diagonal, 0.0f};
		columns[3] = {0.0f, 0.0f, 0.0f, diagonal};
	}

	inline mat4::mat4 (const void* data) {
		memcpy(elements, data, sizeof(float) * MAT4_ELEMENT_COUNT);
	}

	inline mat4::mat4 (const mat4& other) {
		memcpy(elements, other.elements, sizeof(float) * MAT4_ELEMENT_COUNT);
	}

	inline mat4::~mat4 () {}

	inline mat4& mat4::operator+= (const mat4& other) {
		for (int i = 0; i < MAT4_ELEMENT_COUNT; i++)
			elements[i] += other.elements[i];
		return *this;
	}

	inline mat4 mat4::operator+ (const mat4& other) const {
		mat4 result = *this;
		return result += other;
	}

	inline mat4& mat4::operator+= (const float& scalar) {
		for (int i = 0; i < MAT4_ELEMENT_COUNT; i++)
			elements[i] += scalar;
		return *this;
	}

	inline mat4 mat4::operator+ (const float& scalar) const {
		mat4 result = *this;
		return result += scalar;
	}

	inline mat4& mat4::operator-= (const mat4& other) {
		for (int i = 0; i < MAT4_ELEMENT_COUNT; ++i)
			elements[i] -= other.elements[i];
		return *this;
	}

	inline mat4 mat4::operator- (const mat4& other) const {
		mat4 result = *this;
		return result -= other;
	}

	inline mat4& mat4::operator-= (const float& scalar) {
		for (int i = 0; i < MAT4_ELEMENT_COUNT; --i)
			elements[i] -= scalar;
		return *this;
	}

	inline mat4 mat4::operator- (const float& scalar) const {
		mat4 result = *this;
		result -= scalar;
		return result;
	}

	inline mat4& mat4::operator*= (const mat4& other) {
		float data[16];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		memcpy(elements, data, 4 * 4 * sizeof(float));
		return *this;
	}

	inline mat4 mat4::operator* (const mat4& other) const {
		mat4 result = *this;
		return result *= other;
	}

	inline mat4& mat4::operator*= (const float& scalar) {
		for (int i = 0; i < MAT4_ELEMENT_COUNT; ++i)
			elements[i] *= scalar;
		return *this;
	}

	inline mat4 mat4::operator* (const float& scalar) const {
		mat4 result = *this;
		return result *= scalar;
	}

	inline mat4& mat4::operator/= (const mat4& other) {
		return *this *= other.inversed();
	}

	inline mat4 mat4::operator/ (const mat4& other) const {
		mat4 result = *this;
		return result /= other;
	}

	inline mat4& mat4::operator/= (const float& scalar) {
		for (int i = 0; i < MAT4_ELEMENT_COUNT; ++i)
			elements[i] /= scalar;
		return *this;
	}

	inline mat4 mat4::operator/ (const float& scalar) const {
		mat4 result = *this;
		return result /= scalar;
	}

	inline mat4 mat4::operator- () const {
		return *this * -1.0f;
	}

	inline bool mat4::operator== (const mat4& other) const {
		for (int i = 0; i < MAT4_ELEMENT_COUNT; ++i)
			if (elements[i] != other.elements[i])
				return false;
		return true;
	}

	inline bool mat4::operator!= (const mat4& other) const {
		return !(*this == other);
	}

	inline mat4& mat4::inverse () {
		/* 99% code of this function (method) comes from glu library MESA implementation */
		float* m = this->elements;
    	float inv[16], det;
    	int i;

    	inv[0] = m[5]  * m[10] * m[15] - 
    	         m[5]  * m[11] * m[14] - 
    	         m[9]  * m[6]  * m[15] + 
    	         m[9]  * m[7]  * m[14] +
    	         m[13] * m[6]  * m[11] - 
    	         m[13] * m[7]  * m[10];

    	inv[4] = -m[4]  * m[10] * m[15] + 
    	          m[4]  * m[11] * m[14] + 
    	          m[8]  * m[6]  * m[15] - 
    	          m[8]  * m[7]  * m[14] - 
    	          m[12] * m[6]  * m[11] + 
    	          m[12] * m[7]  * m[10];

    	inv[8] = m[4]  * m[9] * m[15] - 
    	         m[4]  * m[11] * m[13] - 
    	         m[8]  * m[5] * m[15] + 
    	         m[8]  * m[7] * m[13] + 
    	         m[12] * m[5] * m[11] - 
    	         m[12] * m[7] * m[9];

    	inv[12] = -m[4]  * m[9] * m[14] + 
    	           m[4]  * m[10] * m[13] +
    	           m[8]  * m[5] * m[14] - 
    	           m[8]  * m[6] * m[13] - 
    	           m[12] * m[5] * m[10] + 
    	           m[12] * m[6] * m[9];

    	inv[1] = -m[1]  * m[10] * m[15] + 
    	          m[1]  * m[11] * m[14] + 
    	          m[9]  * m[2] * m[15] - 
    	          m[9]  * m[3] * m[14] - 
    	          m[13] * m[2] * m[11] + 
    	          m[13] * m[3] * m[10];

    	inv[5] = m[0]  * m[10] * m[15] - 
    	         m[0]  * m[11] * m[14] - 
    	         m[8]  * m[2] * m[15] + 
    	         m[8]  * m[3] * m[14] + 
    	         m[12] * m[2] * m[11] - 
    	         m[12] * m[3] * m[10];

    	inv[9] = -m[0]  * m[9] * m[15] + 
    	          m[0]  * m[11] * m[13] + 
    	          m[8]  * m[1] * m[15] - 
    	          m[8]  * m[3] * m[13] - 
    	          m[12] * m[1] * m[11] + 
    	          m[12] * m[3] * m[9];

    	inv[13] = m[0]  * m[9] * m[14] - 
    	          m[0]  * m[10] * m[13] - 
    	          m[8]  * m[1] * m[14] + 
    	          m[8]  * m[2] * m[13] + 
    	          m[12] * m[1] * m[10] - 
    	          m[12] * m[2] * m[9];

    	inv[2] = m[1]  * m[6] * m[15] - 
    	         m[1]  * m[7] * m[14] - 
    	         m[5]  * m[2] * m[15] + 
    	         m[5]  * m[3] * m[14] + 
    	         m[13] * m[2] * m[7] - 
    	         m[13] * m[3] * m[6];

    	inv[6] = -m[0]  * m[6] * m[15] + 
    	          m[0]  * m[7] * m[14] + 
    	          m[4]  * m[2] * m[15] - 
    	          m[4]  * m[3] * m[14] - 
    	          m[12] * m[2] * m[7] + 
    	          m[12] * m[3] * m[6];

    	inv[10] = m[0]  * m[5] * m[15] - 
    	          m[0]  * m[7] * m[13] - 
    	          m[4]  * m[1] * m[15] + 
    	          m[4]  * m[3] * m[13] + 
    	          m[12] * m[1] * m[7] - 
    	          m[12] * m[3] * m[5];

    	inv[14] = -m[0]  * m[5] * m[14] + 
    	           m[0]  * m[6] * m[13] + 
    	           m[4]  * m[1] * m[14] - 
    	           m[4]  * m[2] * m[13] - 
    	           m[12] * m[1] * m[6] + 
    	           m[12] * m[2] * m[5];

    	inv[3] = -m[1] * m[6] * m[11] + 
    	          m[1] * m[7] * m[10] + 
    	          m[5] * m[2] * m[11] - 
    	          m[5] * m[3] * m[10] - 
    	          m[9] * m[2] * m[7] + 
    	          m[9] * m[3] * m[6];

    	inv[7] = m[0] * m[6] * m[11] - 
    	         m[0] * m[7] * m[10] - 
    	         m[4] * m[2] * m[11] + 
    	         m[4] * m[3] * m[10] + 
    	         m[8] * m[2] * m[7] - 
    	         m[8] * m[3] * m[6];

    	inv[11] = -m[0] * m[5] * m[11] + 
    	           m[0] * m[7] * m[9] + 
    	           m[4] * m[1] * m[11] - 
    	           m[4] * m[3] * m[9] - 
    	           m[8] * m[1] * m[7] + 
    	           m[8] * m[3] * m[5];

    	inv[15] = m[0] * m[5] * m[10] - 
    	          m[0] * m[6] * m[9] - 
    	          m[4] * m[1] * m[10] + 
    	          m[4] * m[2] * m[9] + 
    	          m[8] * m[1] * m[6] - 
    	          m[8] * m[2] * m[5];

    	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    	if (det == 0)
    	    return *this;

    	det = 1.0 / det;

    	for (i = 0; i < 16; i++)
    	    this->elements[i] = inv[i] * det;

    	return *this;
	}

	inline mat4 mat4::inversed () const {
		mat4 result = *this;
		return result.inverse();
	}

	inline mat4 mat4::ortho (float left, float right, float top, float bot, float zNear, float zFar) {
		mat4 result(1.0f);
		result.elements[0] = 2.0f / (right - left);
		result.elements[5] = 2.0f / (top - bot);
		result.elements[10] = 2.0f / (zNear - zFar);
		result.elements[12] = (right + left) / (left - right);
		result.elements[13] = (top + bot) / (bot - top);
		result.elements[14] = (zFar + zNear) / (zNear - zFar);
		return result;
	}

	inline mat4 mat4::translation (const vec2& p) {
		mat4 result(1.0f);
		result.elements[12] = p.x;
		result.elements[13] = p.y;
		return result;
	}

	inline mat4 mat4::rotation (const float& angle) {
		float c = cosf(angle * DEG_TO_RAD);
		float s = sinf(angle * DEG_TO_RAD);

		mat4 result(1.0f);
		result.elements[0] = c;
		result.elements[1] = -s;
		result.elements[4] = s;
		result.elements[5] = c;

		return result;
	}

	inline mat4 mat4::scalation (const vec2& s) {
		mat4 result(1.0f);

		result.elements[0] = s.x;
		result.elements[5] = s.y;

		return result;
	}

	inline mat4& mat4::translate (const vec2& p) { return *this *= mat4::translation(p); }
	inline mat4& mat4::rotate (const float& angle) { return *this *= mat4::rotation(angle); }
	inline mat4& mat4::scale (const vec2& s) { return *this *= mat4::scalation(s); }

	inline vec4 mat4::row (const int& index) const {
		return vec4(elements[0 + index], elements[4 + index], elements[8 + index], elements[12 + index]);
	}

	inline void mat4::setRow (const vec4& row, const int& index) {
		elements[0 + index] = row.x;
		elements[4 + index] = row.y;
		elements[8 + index] = row.z;
		elements[12 + index] = row.w;
	}

	inline vec4& mat4::operator[] (const int& index) {	return columns[index]; }
	inline vec4 mat4::operator[] (const int& index) const { return columns[index]; }
	
}