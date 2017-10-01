#include "Vec3.h"

namespace Ablaze 
{
	namespace Maths
	{
		Vec3::Vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{

		}

		Vec3::Vec3(const Vec2& vector, float z) : Vec3(vector.x, vector.y, z)
		{

		}

		Vec3::Vec3(float value) : Vec3(value, value, value)
		{

		}

		Vec3::Vec3() : Vec3(0.0f)
		{

		}

		float Vec3::GetLengthSqrd() const
		{
			return x * x + y * y + z * z;
		}

		float Vec3::GetLength() const
		{
			return sqrt(GetLengthSqrd());
		}

		float Vec3::Dot(const Vec3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}
		
		Vec3 Vec3::Cross(const Vec3& other) const
		{
			return Cross(*this, other);
		}

		Vec3 Vec3::Normalize() const
		{
			float length = GetLength();
			return Vec3(x / length, y / length, z / length);
		}

		Vec2 Vec3::xy() const
		{
			return Vec2(x, y);
		}

		Vec2 Vec3::xz() const
		{
			return Vec2(x, z);
		}

		Vec3 Vec3::Add(const Vec3& other) const
		{
			return Vec3(x + other.x, y + other.y, z + other.z);
		}

		Vec3 Vec3::Subtract(const Vec3& other) const
		{
			return Vec3(x - other.x, y - other.y, z - other.z);
		}

		Vec3 Vec3::Multiply(const Vec3& other) const
		{
			return Vec3(x * other.x, y * other.y, z * other.z);
		}

		Vec3 Vec3::Divide(const Vec3& other) const
		{
			return Vec3(x / other.x, y / other.y, z / other.z);
		}

		float Vec3::Distance(const Vec3& a, const Vec3& b)
		{
			return (a - b).GetLength();
		}

		Vec3 Vec3::Cross(const Vec3& v1, const Vec3& v2)
		{
			return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
		}

		String Vec3::ToString() const
		{
			return "Vec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
		}

		// operators

		Vec3 operator+(const Vec3& left, const Vec3& right)
		{
			return left.Add(right);
		}

		Vec3 operator-(const Vec3& left, const Vec3& right)
		{
			return left.Subtract(right);
		}

		Vec3 operator*(const Vec3& left, const Vec3& right)
		{
			return left.Multiply(right);
		}

		Vec3 operator/(const Vec3& left, const Vec3& right)
		{
			return left.Divide(right);
		}

		Vec3 operator+(const Vec3& left, float value)
		{
			return Vec3(left.x + value, left.y + value, left.z + value);
		}

		Vec3 operator-(const Vec3& left, float value)
		{
			return Vec3(left.x - value, left.y - value, left.z - value);
		}

		Vec3 operator*(const Vec3& left, float value)
		{
			return Vec3(left.x * value, left.y * value, left.z * value);
		}

		Vec3 operator/(const Vec3& left, float value)
		{
			return Vec3(left.x / value, left.y / value, left.z / value);
		}

		bool Vec3::operator==(const Vec3& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool Vec3::operator!=(const Vec3& other) const
		{
			return !(*this == other);
		}

		Vec3 Vec3::operator+=(const Vec3& other)
		{
			*this = *this + other;
			return *this;
		}

		Vec3 Vec3::operator-=(const Vec3& other)
		{
			*this = *this - other;
			return *this;
		}

		Vec3 Vec3::operator*=(const Vec3& other)
		{
			*this = *this * other;
			return *this;
		}

		Vec3 Vec3::operator/=(const Vec3& other)
		{
			*this = *this / other;
			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
		{
			stream << vector.ToString();
			return stream;
		}
	}
}