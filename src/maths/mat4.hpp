#pragma once

#include <math.h>

namespace kekule {

	inline mat4::mat4 () {}

	inline mat4::mat4 (const float& diagonal) {
		columns[0] = { diagonal,	0.0f,		0.0f,		0.0f };
		columns[1] = { 0.0f,		diagonal,	0.0f,		0.0f };
		columns[2] = { 0.0f,		0.0f,		diagonal,	0.0f };
		columns[3] = { 0.0f,		0.0f,		0.0f,		diagonal };
	}

	inline mat4::mat4 (const float* elements) {
		memcpy (this->elements, elements, sizeof(float) * MAT4_ELEMENT_COUNT);
	}

	inline mat4::mat4 (const vec4* columns) {
		memcpy (this->columns, columns, sizeof(vec4) * MAT4_DIMENSION);
	}

	inline mat4::mat4 (const vec4& c1, const vec4& c2, const vec4& c3, const vec4& c4) {
		this->columns[0] = c1;
		this->columns[1] = c2;
		this->columns[2] = c3;
		this->columns[3] = c4;
	}

	inline mat4::mat4 (const mat4& other) {
		memcpy(this->elements, other.elements, sizeof(float) * MAT4_ELEMENT_COUNT);
	}

	inline mat4::~mat4 () {}

	inline mat4 mat4::operator+ (const mat4& other) const {
		mat4 result;
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			result[i] = this->columns[i] + other.columns[i];
		return result;
	}

	inline mat4& mat4::operator+= (const mat4& other) {
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			(*this)[i] += other.columns[i];
		return *this;
	}

	inline mat4 mat4::operator+ (const float& scalar) const {
		mat4 result;
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			result[i] = this->columns[i] + scalar;
		return result;
	}

	inline mat4& mat4::operator+= (const float& scalar) {
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			(*this)[i] += scalar;
		return *this;
	}

	inline mat4 mat4::operator- (const mat4& other) const {
		mat4 result;
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			result[i] = this->columns[i] - other.columns[i];
		return result;
	}

	inline mat4& mat4::operator-= (const mat4& other) {
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			(*this)[i] -= other.columns[i];
		return *this;
	}

	inline mat4 mat4::operator- (const float& scalar) const {
		mat4 result;
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			result[i] = this->columns[i] - scalar;
		return result;
	}

	inline mat4& mat4::operator-= (const float& scalar) {
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			(*this)[i] -= scalar;
		return *this;
	}

	inline mat4 mat4::operator* (const mat4& other) const {
		mat4 result;
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			for (unsigned char j = 0; j < MAT4_DIMENSION; j++)
				result[j][i] = (this->row(i) * other.column(j)).sum();
		return result;
	}

	inline mat4& mat4::operator*= (const mat4& other) {
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++)
			for (unsigned char j = 0; j < MAT4_DIMENSION; j++)
				(*this)[j][i] = (this->row(i) * other.column(j)).sum();
		return *this;
	}

	inline mat4 mat4::operator* (const float& scalar) const {
		mat4 result;
		for (unsigned char i = 0; i < MAT4_ELEMENT_COUNT; i++)
			result.elements[i] *= scalar;
		return result;
	}

	inline mat4& mat4::operator*= (const float& scalar) {
		for (unsigned char i = 0; i < MAT4_ELEMENT_COUNT; i++)
			this->columns[i] *= scalar;
		return *this;
	}

	inline vec4& mat4::operator[] (const unsigned int& index) {
		return this->columns[index];
	}

	inline vec4 mat4::column (const unsigned int& index) const {
		return this->columns[index];
	}

	inline vec4 mat4::row (const unsigned int& index) const {
		return vec4 (
			this->elements[0 * 4 + index],
			this->elements[1 * 4 + index],
			this->elements[2 * 4 + index],
			this->elements[3 * 4 + index]
		);
	}

	inline float mat4::at (const unsigned int& column, const unsigned int& row) const {
		return this->elements[4 * column + row];
	}

	inline bool mat4::operator== (const mat4& other) const {
		for (unsigned char i = 0; i < MAT4_ELEMENT_COUNT; i++)
			if (this->elements[i] != other.elements[i])
				return false;
		return true;
	}

	inline bool mat4::operator!= (const mat4& other) const {
		for (unsigned char i = 0; i < MAT4_ELEMENT_COUNT; i++)
			if (this->elements[i] != other.elements[i])
				return true;
		return false;
	}

	inline mat4& mat4::scale (const vec3& axis) {
		mat4 result(1.0f);
		result[0][0] = axis.x;
		result[1][1] = axis.y;
		result[2][2] = axis.z;
		*this *= result;
		return *this;
	}

	inline mat4 mat4::scalation (const vec3& axis) {
		mat4 result(1.0f);
		result[0][0] = axis.x;
		result[1][1] = axis.y;
		result[2][2] = axis.z;
		return result;
	}

	inline mat4& mat4::translate (const vec3& v) {
		mat4 result(1.0f);
		result[3][0] = v.x;
		result[3][1] = v.y;
		result[3][3] = v.z;
		*this *= result;
		return *this;
	}

	inline mat4 mat4::translation (const vec3& v) {
		mat4 result(1.0f);
		result[3][0] = v.x;
		result[3][1] = v.y;
		result[3][3] = v.z;
		return result;
	}

	inline mat4& mat4::rotate (const float& angle, vec3 axis, const bool& normalized) {
		mat4 result(1.0f);

		float c = cosf(angle * DEG_TO_RAD);
		float s = sinf(angle * DEG_TO_RAD);
		float omc = 1 - c;

		if (!normalized)
			axis.normalize();

		result[0][0] = c + axis.x * axis.x * omc;
		result[0][1] = axis.y * axis.x * omc + axis.z * s;
		result[0][2] = axis.z * axis.x * omc - axis.y * s;

		result[1][0] = axis.x * axis.y * omc - axis.z * s;
		result[1][1] = c + axis.y * axis.y * omc;
		result[1][2] = axis.z * axis.y * omc + axis.x * s;

		result[2][0] = axis.x * axis.z * omc + axis.y * s;
		result[2][1] = axis.y * axis.z * omc - axis.x * s;
		result[2][2] = c + axis.z * axis.z * omc;
		*this *= result;
		return *this;
	}

	inline mat4 mat4::rotation (const float& angle, vec3 axis, const bool& normalized) {
		mat4 result(1.0f);

		float c = cosf(angle * DEG_TO_RAD);
		float s = sinf(angle * DEG_TO_RAD);
		float omc = 1 - c;

		if (!normalized)
			axis.normalize();

		result[0][0] = c + axis.x * axis.x * omc;
		result[0][1] = axis.y * axis.x * omc + axis.z * s;
		result[0][2] = axis.z * axis.x * omc - axis.y * s;

		result[1][0] = axis.x * axis.y * omc - axis.z * s;
		result[1][1] = c + axis.y * axis.y * omc;
		result[1][2] = axis.z * axis.y * omc + axis.x * s;

		result[2][0] = axis.x * axis.z * omc + axis.y * s;
		result[2][1] = axis.y * axis.z * omc - axis.x * s;
		result[2][2] = c + axis.z * axis.z * omc;
		return result;
	}

	inline mat4 mat4::ortho(const float& left, const float& right, const float& top, const float& bottom, const float& zfar, const float& znear) {
		mat4 result(1.0f);

		result[0][0] = 2 / (right - left);
		result[1][1] = 2 / (top - bottom);
		result[2][2] = 2 / (znear - zfar);

		result[3][0] = (right + left) / (left - right);
		result[3][1] = (top + bottom) / (bottom - top);
		result[3][2] = (zfar + znear) / (znear - zfar);
		return result;
	}

	inline void mat4::setColumn (const unsigned int& index, const vec4& column) {
		this->columns[index] = column;
	}

	inline void mat4::setRow(const unsigned int& index, const vec4& row) {
		this->columns[0][index] = row.x;
		this->columns[1][index] = row.y;
		this->columns[2][index] = row.z;
		this->columns[3][index] = row.w;
	}

	inline void mat4::print (std::ostream& os) const {
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++) {
			vec4 row = this->row(i);
			os << '\t' << row.x << ' ' << row.y << ' ' << row.z << ' ' << row.w << '\n';
		}
	}

	inline vec4 operator* (const mat4& m, const vec4& v) {
		vec4 result;
		result.x = (m.row(0) * v).sum();
		result.x = (m.row(1) * v).sum();
		result.x = (m.row(2) * v).sum();
		result.x = (m.row(3) * v).sum();
		return result;
	}

	inline vec4 operator* (const vec4& v, const mat4& m) {
		vec4 result;
		result.x = (m.row(0) * v).sum();
		result.x = (m.row(1) * v).sum();
		result.x = (m.row(2) * v).sum();
		result.x = (m.row(3) * v).sum();
		return result;
	}

	inline vec4& operator*= (vec4& v, const mat4& m) {
		v.x = (m.row(0) * v).sum();
		v.x = (m.row(1) * v).sum();
		v.x = (m.row(2) * v).sum();
		v.x = (m.row(3) * v).sum();
		return v;
	}

	inline std::ostream& operator<< (std::ostream& os, const mat4& m) {
		for (unsigned char i = 0; i < MAT4_DIMENSION; i++) {
			vec4 row = m.row(i);
			os << '\t' << row.x << ' ' << row.y << ' ' << row.z << ' ' << row.w << '\n';
		}
		return os;
	}
}