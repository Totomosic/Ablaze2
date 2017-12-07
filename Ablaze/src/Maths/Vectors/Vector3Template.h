#pragma once
#include "Object.h"

#define AB_MATHS_VECTOR3_CLASS_TEMPLATE_HEADER(name, type, vec2)	\
public:	\
	type x;	\
	type y; \
	type z;	\
	\
public:	\
	name(type x, type y, type z);	\
	name(const vec2& vec, type z);	\
	name(const vec2& vec);	\
	name(type value);	\
	name();	\
	\
	const type Get(int index) const;	\
	type& Get(int index);	\
	const type operator[](int index) const; \
	type& operator[](int index);	\
	\
	type LengthSqrd() const;	\
	type Length() const;	\
	type MagnitudeSqrd() const;	\
	type Magnitude() const;	\
	\
	type Dot(const name& other) const;	\
	name Cross(const name& other) const;	\
	name Normalize() const;	\
	\
public:	\
	name Add(const name& rhs) const;	\
	name Add(type rhs) const;	\
	name Sub(const name& rhs) const;	\
	name Sub(type rhs) const;	\
	name Mul(const name& rhs) const;	\
	name Mul(type rhs) const;	\
	name Div(const name& rhs) const;	\
	name Div(type rhs) const;	\
	\
	friend name operator+(const name& left, const name& right);	\
	friend name operator+(const name& left, type right);	\
	friend name operator+(type left, const name& right);	\
	friend name operator-(const name& left, const name& right);	\
	friend name operator-(const name& left, type right);	\
	friend name operator-(type left, const name& right);	\
	friend name operator*(const name& left, const name& right);	\
	friend name operator*(const name& left, type right);	\
	friend name operator*(type left, const name& right);	\
	friend name operator/(const name& left, const name& right);	\
	friend name operator/(const name& left, type right);	\
	friend name operator/(type left, const name& right);	\
	\
	name& operator+=(const name& right);	\
	name& operator+=(type right);	\
	name& operator-=(const name& right);	\
	name& operator-=(type right);	\
	name& operator*=(const name& right);	\
	name& operator*=(type right);	\
	name& operator/=(const name& right);	\
	name& operator/=(type right);	\
	\
	bool operator==(const name& other) const;	\
	bool operator!=(const name& other) const;	\
	name operator-() const;	\
	\
	String ToString() const;	\
	friend std::ostream& operator<<(std::ostream& stream, const name& vector);	\
	\
	vec2 xy() const;	\
	\
public:	\
	static name Cross(const name& left, const name& right);	\
	static type Distance(const name& left, const name& right);	\
	static name Right();	\
	static name Up();	\
	static name Forward();

#define AB_MATHS_VECTOR3_CLASS_TEMPLATE_CPP(name, type, vec2)	\
name::name(type x, type y, type z)	\
	: x(x), y(y), z(z)	\
{	\
	\
}	\
	\
name::name(const vec2& vec2, type z) : name(vec2.x, vec2.y, z)	\
{	\
	\
}	\
	\
name::name(const vec2& vec2) : name(vec2.x, vec2.y, (type)0)	\
{	\
	\
}	\
	\
name::name(type value) : name(value, value)	\
{	\
	\
}	\
	\
name::name() : name((type)0)	\
{	\
	\
}	\
	\
const type name::Get(int index) const	\
{	\
	switch(index)	\
	{	\
	case 0:	\
		return x;	\
	case 1:	\
		return y;	\
	case 2:	\
		return z;	\
	default:	\
		AB_ASSERT(false);	\
	}	\
}	\
	\
type& name::Get(int index)	\
{	\
	switch (index)	\
	{	\
	case 0:	\
		return x;	\
	case 1:	\
		return y;	\
	case 2:	\
		return z;	\
	default:	\
		AB_ASSERT(false);	\
	}	\
}	\
	\
const type name::operator[](int index) const	\
{	\
	return Get(index);	\
}	\
	\
type& name::operator[](int index)	\
{	\
	return Get(index);	\
}	\
	\
type name::LengthSqrd() const	\
{	\
	return x * x + y * y + z * z;	\
}	\
	\
type name::Length() const	\
{	\
	return sqrt(LengthSqrd());	\
}	\
	\
type name::MagnitudeSqrd() const	\
{	\
	return LengthSqrd();	\
}	\
	\
type name::Magnitude() const	\
{	\
	return Length();	\
}	\
	\
type name::Dot(const name& other) const	\
{	\
	return x * other.x + y * other.y + z * other.z;	\
}	\
	\
name name::Cross(const name& other) const	\
{	\
	return name::Cross(*this, other);	\
}	\
	\
name name::Normalize() const	\
{	\
	return *this / Length();	\
}	\
	\
name name::Add(const name& other) const	\
{	\
	return name(x + other.x, y + other.y, z + other.z);	\
}	\
	\
name name::Add(type other) const	\
{	\
	return name(x + other, y + other, z + other);	\
}	\
	\
name name::Sub(const name& other) const	\
{	\
	return name(x - other.x, y - other.y, z - other.z);	\
}	\
	\
name name::Sub(type other) const	\
{	\
	return name(x - other, y - other, z - other);	\
}	\
	\
name name::Mul(const name& other) const	\
{	\
	return name(x * other.x, y * other.y, z * other.z);	\
}	\
	\
name name::Mul(type other) const	\
{	\
	return name(x * other, y * other, z * other);	\
}	\
	\
name name::Div(const name& other) const	\
{	\
	return name(x / other.x, y / other.y, z / other.z);	\
}	\
	\
name name::Div(type other) const	\
{	\
	return name(x / other, y / other, z / other);	\
}	\
	\
name operator+(const name& left, const name& right)	\
{	\
	return left.Add(right);	\
}	\
	\
name operator+(const name& left, type right)	\
{	\
	return left.Add(right);	\
}	\
	\
name operator+(type left, const name& right)	\
{	\
	return name(left + right.x, left + right.y, left + right.z);	\
}	\
	\
name operator-(const name& left, const name& right)	\
{	\
	return left.Sub(right);	\
}	\
	\
name operator-(const name& left, type right)	\
{	\
	return left.Sub(right);	\
}	\
	\
name operator-(type left, const name& right)	\
{	\
	return name(left - right.x, left - right.y, left - right.z);	\
}	\
	\
name operator*(const name& left, const name& right)	\
{	\
	return left.Mul(right);	\
}	\
	\
name operator*(const name& left, type right)	\
{	\
	return left.Mul(right);	\
}	\
	\
name operator*(type left, const name& right)	\
{	\
	return name(left * right.x, left * right.y, left * right.z);	\
}	\
	\
name operator/(const name& left, const name& right)	\
{	\
	return left.Div(right);	\
}	\
	\
name operator/(const name& left, type right)	\
{	\
	return left.Div(right);	\
}	\
	\
name operator/(type left, const name& right)	\
{	\
	return name(left / right.x, left / right.y, left / right.z);	\
}	\
	\
name& name::operator+=(const name& other)	\
{	\
	*this = *this + other;	\
	return *this;	\
}	\
	\
name& name::operator+=(type other)	\
{	\
	*this = *this + other;	\
	return *this;	\
}	\
	\
name& name::operator-=(const name& other)	\
{	\
	*this = *this - other;	\
	return *this;	\
}	\
	\
name& name::operator-=(type other)	\
{	\
	*this = *this - other;	\
	return *this;	\
}	\
	\
name& name::operator*=(const name& other)	\
{	\
	*this = *this * other;	\
	return *this;	\
}	\
	\
name& name::operator*=(type other)	\
{	\
	*this = *this * other;	\
	return *this;	\
}	\
	\
name& name::operator/=(const name& other)	\
{	\
	*this = *this / other;	\
	return *this;	\
}	\
	\
name& name::operator/=(type other)	\
{	\
	*this = *this / other;	\
	return *this;	\
}	\
	\
bool name::operator==(const name& other) const	\
{	\
	return (x == other.x && y == other.y && z == other.z);	\
}	\
	\
bool name::operator!=(const name& other) const	\
{	\
	return !(*this == other);	\
}	\
	\
name name::operator-() const	\
{	\
	return name(-x, -y, -z);	\
}	\
	\
String name::ToString() const	\
{	\
	return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";	\
}	\
	\
std::ostream& operator<<(std::ostream& stream, const name& vector)	\
{	\
	stream << vector.ToString();	\
	return stream;	\
}	\
	\
vec2 name::xy() const	\
{	\
	return vec2(x, y);	\
}	\
	\
name name::Cross(const name& left, const name& right)	\
{	\
	return name(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);	\
}	\
	\
type name::Distance(const name& left, const name& right)	\
{	\
	return (left - right).Length();	\
}	\
	\
name name::Right()	\
{	\
	return name((type)1, (type)0, (type)0);	\
}	\
	\
name name::Up()	\
{	\
	return name((type)0, (type)1, (type)0);	\
}	\
	\
name name::Forward()	\
{	\
	return name((type)0, (type)0, (type)-1);	\
}