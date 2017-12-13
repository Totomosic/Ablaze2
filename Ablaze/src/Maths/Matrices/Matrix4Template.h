#pragma once
#include "Matrix4Template.h"

#define AB_MATHS_MATRIX4_CLASS_TEMPLATE_HEADER(name, type, vec4, vec3, vec2)	\
public:	\
	type values[16];	\
	\
public:	\
	name(type values[16]);	\
	name(const vec4& diagonal);	\
	name(type diagonal);	\
	name();	\
	\
	vec4 Column(int index) const;	\
	vec4 Row(int index) const;	\
	const type Element(int index) const;	\
	type& Element(int index);	\
	const type Element(int row, int col) const;	\
	type& Element(int row, int col);	\
	\
	const type operator[](int index) const;	\
	type& operator[](int index);	\
	\
	void SetColumn(int index, const vec4& column);	\
	void SetRow(int index, const vec4& row);	\
	void SetElement(int row, int col, type value);	\
	\
	name Inverse() const;	\
	\
	name operator-() const;	\
	friend name operator+(const name& left, const name& right);	\
	friend name operator+(const name& left, type right);	\
	friend name operator+(type left, const name& right);	\
	friend name operator-(const name& left, const name& right);	\
	friend name operator-(const name& left, type right);	\
	friend name operator-(type left, const name& right);	\
	friend name operator*(const name& left, const name& right);	\
	friend name operator*(const name& left, type right);	\
	friend name operator*(type left, const name& right);	\
	friend vec4 operator*(const name& left, const vec4& right);	\
	friend vec3 operator*(const name& left, const vec3& right);	\
	friend vec2 operator*(const name& left, const vec2& right);	\
	\
	String ToString() const;	\
	friend std::ostream& operator<<(std::ostream& stream, const name& mat);	\
	\
public:	\
	static name Identity();	\
	static name Zero();	\
	static name FromColumns(const vec4& c0, const vec4& c1, const vec4& c2, const vec4& c3);	\
	static name FromRows(const vec4& r0, const vec4& r1, const vec4& r2, const vec4& r3);	\
	\
	static name Orthographic(type left, type right, type bottom, type top, type near, type far);	\
	static name Perspective(type fov, type aspect, type near, type far);	\
	static name Translation(const vec4& translation);	\
	static name Translation(const vec3& translation);	\
	static name Translation(type x, type y, type z);	\
	static name Translation(const vec2& translation);	\
	static name Rotation(type angle, const vec4& axis);	\
	static name Rotation(type angle, const vec3& axis);	\
	static name Scale(const vec4& scale);	\
	static name Scale(const vec3& scale);	\
	static name Scale(type x, type y, type z);	\
	static name Scale(const vec2& scale);	\
	static name Scale(type scale);	\
	\
	static name InvertX(const name& mat);	\
	static name InvertY(const name& mat);	\
	static name InvertZ(const name& mat);

#define AB_MATHS_MATRIX4_CLASS_TEMPLATE_CPP(name, type, vec4, vec3, vec2)	\
name::name(type elements[16]) : name()	\
{	\
	for (int i = 0; i < 16; i++)	\
	{	\
		values[i] = elements[i];	\
	}	\
}	\
	\
name::name(const vec4& diagonal) : name()	\
{	\
	values[4 * 0 + 0] = diagonal.x;	\
	values[4 * 1 + 1] = diagonal.y;	\
	values[4 * 2 + 2] = diagonal.z;	\
	values[4 * 3 + 3] = diagonal.w;	\
}	\
	\
name::name(type diagonal) : name(vec4(diagonal, diagonal, diagonal, diagonal))	\
{	\
	\
}	\
	\
name::name()	\
{	\
	for (int i = 0; i < 16; i++)	\
	{	\
		values[i] = (type)0;	\
	}	\
}	\
	\
vec4 name::Column(int index) const	\
{	\
	AB_ASSERT(index < 4);	\
	return vec4(values[4 * index + 0], values[4 * index + 1], values[4 * index + 2], values[4 * index + 3]);	\
}	\
	\
vec4 name::Row(int index) const	\
{	\
	AB_ASSERT(index < 4);	\
	return vec4(values[4 * 0 + index], values[4 * 1 + index], values[4 * 2 + index], values[4 * 3 + index]);	\
}	\
	\
const type name::Element(int index) const	\
{	\
	AB_ASSERT(index < 16);	\
	return values[index];	\
}	\
	\
type& name::Element(int index)	\
{	\
	AB_ASSERT(index < 16);	\
	return values[index];	\
}	\
	\
const type name::Element(int row, int col) const	\
{	\
	AB_ASSERT(row < 4 && col < 4);	\
	return values[4 * col + row];	\
}	\
	\
type& name::Element(int row, int col)	\
{	\
	AB_ASSERT(row < 4 && col < 4);	\
	return values[4 * col + row];	\
}	\
	\
const type name::operator[](int index) const	\
{	\
	return Element(index);	\
}	\
	\
type& name::operator[](int index)	\
{	\
	return Element(index);	\
}	\
	\
void name::SetColumn(int index, const vec4& column)	\
{	\
	values[4 * index + 0] = column.x;	\
	values[4 * index + 1] = column.y;	\
	values[4 * index + 2] = column.z;	\
	values[4 * index + 3] = column.w;	\
}	\
	\
void name::SetRow(int index, const vec4& row)	\
{	\
	values[4 * 0 + index] = row.x;	\
	values[4 * 1 + index] = row.y;	\
	values[4 * 2 + index] = row.z;	\
	values[4 * 3 + index] = row.w;	\
}	\
	\
void name::SetElement(int row, int col, type value)	\
{	\
	values[4 * col + row] = value;	\
}	\
	\
name name::Inverse() const	\
{	\
	type inv[16];	\
	type invOut[16];	\
	type det;	\
	int i;	\
	\
	inv[0] = values[5] * values[10] * values[15] -	\
		values[5] * values[11] * values[14] -	\
		values[9] * values[6] * values[15] +	\
		values[9] * values[7] * values[14] +	\
		values[13] * values[6] * values[11] -	\
		values[13] * values[7] * values[10];	\
	\
	inv[4] = -values[4] * values[10] * values[15] +	\
		values[4] * values[11] * values[14] +	\
		values[8] * values[6] * values[15] -	\
		values[8] * values[7] * values[14] -	\
		values[12] * values[6] * values[11] +	\
		values[12] * values[7] * values[10];	\
	\
	inv[8] = values[4] * values[9] * values[15] -	\
		values[4] * values[11] * values[13] -	\
		values[8] * values[5] * values[15] +	\
		values[8] * values[7] * values[13] +	\
		values[12] * values[5] * values[11] -	\
		values[12] * values[7] * values[9];	\
	\
	inv[12] = -values[4] * values[9] * values[14] +	\
		values[4] * values[10] * values[13] +	\
		values[8] * values[5] * values[14] -	\
		values[8] * values[6] * values[13] -	\
		values[12] * values[5] * values[10] +	\
		values[12] * values[6] * values[9];	\
	\
	inv[1] = -values[1] * values[10] * values[15] +	\
		values[1] * values[11] * values[14] +	\
		values[9] * values[2] * values[15] -	\
		values[9] * values[3] * values[14] -	\
		values[13] * values[2] * values[11] +	\
		values[13] * values[3] * values[10];	\
	\
	inv[5] = values[0] * values[10] * values[15] -	\
		values[0] * values[11] * values[14] -	\
		values[8] * values[2] * values[15] +	\
		values[8] * values[3] * values[14] +	\
		values[12] * values[2] * values[11] -	\
		values[12] * values[3] * values[10];	\
	\
	inv[9] = -values[0] * values[9] * values[15] +	\
		values[0] * values[11] * values[13] +	\
		values[8] * values[1] * values[15] -	\
		values[8] * values[3] * values[13] -	\
		values[12] * values[1] * values[11] +	\
		values[12] * values[3] * values[9];	\
	\
	inv[13] = values[0] * values[9] * values[14] -	\
		values[0] * values[10] * values[13] -	\
		values[8] * values[1] * values[14] +	\
		values[8] * values[2] * values[13] +	\
		values[12] * values[1] * values[10] -	\
		values[12] * values[2] * values[9];	\
	\
	inv[2] = values[1] * values[6] * values[15] -	\
		values[1] * values[7] * values[14] -	\
		values[5] * values[2] * values[15] +	\
		values[5] * values[3] * values[14] +	\
		values[13] * values[2] * values[7] -	\
		values[13] * values[3] * values[6];	\
	\
	inv[6] = -values[0] * values[6] * values[15] +	\
		values[0] * values[7] * values[14] +	\
		values[4] * values[2] * values[15] -	\
		values[4] * values[3] * values[14] -	\
		values[12] * values[2] * values[7] +	\
		values[12] * values[3] * values[6];	\
	\
	inv[10] = values[0] * values[5] * values[15] -	\
		values[0] * values[7] * values[13] -	\
		values[4] * values[1] * values[15] +	\
		values[4] * values[3] * values[13] +	\
		values[12] * values[1] * values[7] -	\
		values[12] * values[3] * values[5];	\
	\
	inv[14] = -values[0] * values[5] * values[14] +	\
		values[0] * values[6] * values[13] +	\
		values[4] * values[1] * values[14] -	\
		values[4] * values[2] * values[13] -	\
		values[12] * values[1] * values[6] +	\
		values[12] * values[2] * values[5];	\
	\
	inv[3] = -values[1] * values[6] * values[11] +	\
		values[1] * values[7] * values[10] +	\
		values[5] * values[2] * values[11] -	\
		values[5] * values[3] * values[10] -	\
		values[9] * values[2] * values[7] +	\
		values[9] * values[3] * values[6];	\
	\
	inv[7] = values[0] * values[6] * values[11] -	\
		values[0] * values[7] * values[10] -	\
		values[4] * values[2] * values[11] +	\
		values[4] * values[3] * values[10] +	\
		values[8] * values[2] * values[7] -	\
		values[8] * values[3] * values[6];	\
	\
	inv[11] = -values[0] * values[5] * values[11] +	\
		values[0] * values[7] * values[9] +	\
		values[4] * values[1] * values[11] -	\
		values[4] * values[3] * values[9] -	\
		values[8] * values[1] * values[7] +	\
		values[8] * values[3] * values[5];	\
	\
	inv[15] = values[0] * values[5] * values[10] -	\
		values[0] * values[6] * values[9] -	\
		values[4] * values[1] * values[10] +	\
		values[4] * values[2] * values[9] +	\
		values[8] * values[1] * values[6] -	\
		values[8] * values[2] * values[5];	\
	\
	det = values[0] * inv[0] + values[1] * inv[4] + values[2] * inv[8] + values[3] * inv[12];	\
	\
	if (det == (type)0)	\
	{	\
		AB_ERROR("Matrix could not be inverted");	\
		return Identity();	\
	}	\
	\
	det = (type)1 / det;	\
	\
	for (i = 0; i < 16; i++)	\
	{	\
		invOut[i] = inv[i] * det;	\
	}	\
	\
	return name(invOut);	\
}	\
	\
name name::operator-() const	\
{	\
	return *this * (type)-1;	\
}	\
	\
name operator+(const name& left, const name& right)	\
{	\
	name result;	\
	for (int i = 0; i < 16; i++)	\
	{	\
		result.values[i] = left.values[i] + right.values[i];	\
	}	\
	return result;	\
}	\
	\
name operator+(const name& left, type right)	\
{	\
	name result;	\
	for (int i = 0; i < 16; i++)	\
	{	\
		result.values[i] = left.values[i] + right;	\
	}	\
	return result;	\
}	\
	\
name operator+(type left, const name& right)	\
{	\
	return right + left;	\
}	\
	\
name operator-(const name& left, const name& right)	\
{	\
	name result;	\
	for (int i = 0; i < 16; i++)	\
	{	\
		result.values[i] = left.values[i] - right.values[i];	\
	}	\
	return result;	\
}	\
	\
name operator-(const name& left, type right)	\
{	\
	name result;	\
	for (int i = 0; i < 16; i++)	\
	{	\
		result.values[i] = left.values[i] - right;	\
	}	\
	return result;	\
}	\
	\
name operator-(type left, const name& right)	\
{	\
	name result;	\
	for (int i = 0; i < 16; i++)	\
	{	\
		result.values[i] = left - right.values[i];	\
	}	\
	return result;	\
}	\
	\
name operator*(const name& left, const name& right)	\
{	\
	name result;	\
	for (int y = 0; y < 4; y++)	\
	{	\
		for (int x = 0; x < 4; x++)	\
		{	\
			type sum = (type)0;	\
			for (int e = 0; e < 4; e++)	\
			{	\
				sum += left.values[x + e * 4] * right.values[e + y * 4];	\
			}	\
			result.values[x + y * 4] = sum;	\
		}	\
	}	\
	return result;	\
}	\
	\
name operator*(const name& left, type right)	\
{	\
	name result;	\
	for (int i = 0; i < 16; i++)	\
	{	\
		result.values[i] = left.values[i] * right;	\
	}	\
	return result;	\
}	\
	\
name operator*(type left, const name& right)	\
{	\
	return right * left;	\
}	\
	\
vec4 operator*(const name& left, const vec4& right)	\
{	\
	type x = left.values[4 * 0 + 0] * right.x + left.values[4 * 1 + 0] * right.y + left.values[4 * 2 + 0] * right.z + left.values[4 * 3 + 0] * right.w;	\
	type y = left.values[4 * 0 + 1] * right.x + left.values[4 * 1 + 1] * right.y + left.values[4 * 2 + 1] * right.z + left.values[4 * 3 + 1] * right.w;	\
	type z = left.values[4 * 0 + 2] * right.x + left.values[4 * 1 + 2] * right.y + left.values[4 * 2 + 2] * right.z + left.values[4 * 3 + 2] * right.w;	\
	type w = left.values[4 * 0 + 3] * right.x + left.values[4 * 1 + 3] * right.y + left.values[4 * 2 + 3] * right.z + left.values[4 * 3 + 3] * right.w;	\
	return vec4(x, y, z, w);	\
}	\
	\
vec3 operator*(const name& left, const vec3& right)	\
{	\
	vec4 result = left * vec4(right, (type)1);	\
	return result.xyz(); \
}	\
	\
vec2 operator*(const name& left, const vec2& right)	\
{	\
	vec3 result = left * vec3(right, (type)0);	\
	return result.xy();	\
}	\
	\
String name::ToString() const	\
{	\
	String s = " ";	\
	String result = "|" + std::to_string(values[0 + 0 * 4]) + s + std::to_string(values[0 + 1 * 4]) + s + std::to_string(values[0 + 2 * 4]) + s + std::to_string(values[0 + 3 * 4]) + "|" + "\n"	\
		+ "|" + std::to_string(values[1 + 0 * 4]) + s + std::to_string(values[1 + 1 * 4]) + s + std::to_string(values[1 + 2 * 4]) + s + std::to_string(values[1 + 3 * 4]) + "|" + "\n"	\
		+ "|" + std::to_string(values[2 + 0 * 4]) + s + std::to_string(values[2 + 1 * 4]) + s + std::to_string(values[2 + 2 * 4]) + s + std::to_string(values[2 + 3 * 4]) + "|" + "\n"	\
		+ "|" + std::to_string(values[3 + 0 * 4]) + s + std::to_string(values[3 + 1 * 4]) + s + std::to_string(values[3 + 2 * 4]) + s + std::to_string(values[3 + 3 * 4]) + "|";	\
	return result;	\
}	\
	\
std::ostream& operator<<(std::ostream& stream, const name& right)	\
{	\
	stream << right.ToString();	\
	return stream;	\
}	\
	\
name name::Identity()	\
{	\
	return name((type)1);	\
}	\
	\
name name::Zero()	\
{	\
	return name((type)0);	\
}	\
	\
name name::FromColumns(const vec4& c0, const vec4& c1, const vec4& c2, const vec4& c3)	\
{	\
	name result;	\
	result.SetColumn(0, c0);	\
	result.SetColumn(1, c1);	\
	result.SetColumn(2, c2);	\
	result.SetColumn(3, c3);	\
	return result;	\
}	\
	\
name name::FromRows(const vec4& r0, const vec4& r1, const vec4& r2, const vec4& r3)	\
{	\
	name result;	\
	result.SetRow(0, r0);	\
	result.SetRow(1, r1);	\
	result.SetRow(2, r2);	\
	result.SetRow(3, r3);	\
	return result;	\
}	\
	\
name name::Orthographic(type left, type right, type bottom, type top, type nearPlane, type farPlane)	\
{	\
	name result = Identity();	\
	\
	result.values[0 + 0 * 4] = (type)2 / (right - left);	\
	result.values[1 + 1 * 4] = (type)2 / (top - bottom);	\
	result.values[2 + 2 * 4] = (type)-2 / (farPlane - nearPlane);	\
	\
	result.values[0 + 3 * 4] = -(left + right) / (right - left);	\
	result.values[1 + 3 * 4] = -(bottom + top) / (top - bottom);	\
	result.values[2 + 3 * 4] = -(farPlane + nearPlane) / (farPlane - nearPlane);	\
	\
	return result;	\
}	\
	\
name name::Perspective(type fov, type aspect, type nearPlane, type farPlane)	\
{	\
	name result = Identity();	\
	\
	float q = (type)1 / (type)tan(0.5f * fov);	\
	float a = q / aspect;	\
	\
	float b = (nearPlane + farPlane) / (nearPlane - farPlane);	\
	float c = ((type)2 * nearPlane * farPlane) / (nearPlane - farPlane);	\
	\
	result.values[0 + 0 * 4] = a;	\
	result.values[1 + 1 * 4] = q;	\
	result.values[2 + 2 * 4] = b;	\
	result.values[3 + 2 * 4] = (type)-1;	\
	result.values[2 + 3 * 4] = c;	\
	\
	return result;	\
}	\
	\
name name::Translation(const vec4& translation)	\
{	\
	name result = Identity();	\
	result.SetColumn(3, translation);	\
	return result;	\
}	\
	\
name name::Translation(const vec3& translation)	\
{	\
	return Translation(vec4(translation, (type)1));	\
}	\
	\
name name::Translation(type x, type y, type z)	\
{	\
	return Translation(vec3(x, y, z));	\
}	\
	\
name name::Translation(const vec2& translation)	\
{	\
	return Translation(vec3(translation, (type)0));	\
}	\
	\
name name::Rotation(type angle, const vec4& axis)	\
{	\
	return Rotation(angle, axis.xyz());	\
}	\
	\
name name::Rotation(type angle, const vec3& axis)	\
{	\
	name result = Identity();	\
	\
	type c = (type)cos(angle);	\
	type s = (type)sin(angle);	\
	type omc = (type)1 - c;	\
	\
	type x = axis.x;	\
	type y = axis.y;	\
	type z = axis.z;	\
	\
	result.values[0 + 0 * 4] = x * omc + c;	\
	result.values[1 + 0 * 4] = y * x * omc + z * s;	\
	result.values[2 + 0 * 4] = x * z * omc - y * s;	\
	\
	result.values[0 + 1 * 4] = x * y * omc - z * s;	\
	result.values[1 + 1 * 4] = y * omc + c;	\
	result.values[2 + 1 * 4] = y * z * omc + x * s;	\
	\
	result.values[0 + 2 * 4] = x * z * omc + y * s;	\
	result.values[1 + 2 * 4] = y * z * omc - x * s;	\
	result.values[2 + 2 * 4] = z * omc + c;	\
	\
	return result;	\
}	\
	\
name name::Scale(const vec4& scale)	\
{	\
	return name(scale);	\
}	\
	\
name name::Scale(const vec3& scale)	\
{	\
	return Scale(vec4(scale, (type)1));	\
}	\
	\
name name::Scale(type x, type y, type z)	\
{	\
	return Scale(vec3(x, y, z));	\
}	\
	\
name name::Scale(const vec2& scale)	\
{	\
	return Scale(vec3(scale, (type)1));	\
}	\
	\
name name::Scale(type scale)	\
{	\
	return Scale(vec3(scale, scale, scale));	\
}	\
	\
name name::InvertX(const name& mat)	\
{	\
	name flipMatrix = Scale((type)-1, (type)1, (type)1);	\
	return flipMatrix * mat * flipMatrix;	\
}	\
	\
name name::InvertY(const name& mat)	\
{	\
	name flipMatrix = Scale((type)1, (type)-1, (type)1);	\
	return flipMatrix * mat * flipMatrix;	\
}	\
	\
name name::InvertZ(const name& mat)	\
{	\
	name flipMatrix = Scale((type)1, (type)1, (type)-1);	\
	return flipMatrix * mat * flipMatrix;	\
}