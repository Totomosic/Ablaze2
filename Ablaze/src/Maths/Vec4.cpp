#include "Vec4.h"

namespace Ablaze
{
	namespace Maths
	{
		Vec4::Vec4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vec4::Vec4(const Vec3& vector, float w) : Vec4::Vec4(vector.x, vector.y, vector.z, w)
		{
		
		}

		Vec4::Vec4(const Vec2& vector, float z, float w) : Vec4::Vec4(vector.x, vector.y, z, w)
		{

		}

		Vec4::Vec4(float xyz, float w) : Vec4::Vec4(xyz, xyz, xyz, w)
		{

		}

		Vec4::Vec4(float value) : Vec4(value, value, value, value)
		{

		}

		float Vec4::Get(int index) const
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				return 0; // Out of range
			}
		}

		float Vec4::GetLengthSqrd() const
		{
			return x * x + y * y + z * z + w * w;
		}

		float Vec4::GetLength() const
		{
			return sqrt(GetLengthSqrd());
		}

		float Vec4::Dot(const Vec4& other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		Vec4 Vec4::Normalize() const
		{
			float length = GetLength();
			return Vec4(x / length, y / length, z / length, w / length);
		}

		Vec3 Vec4::xyz() const
		{
			return Vec3(x, y, z);
		}

		Vec2 Vec4::xy() const
		{
			return Vec2(x, y);
		}

		Vec4 Vec4::Add(const Vec4& other) const
		{
			return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		Vec4 Vec4::Subtract(const Vec4& other) const
		{
			return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		Vec4 Vec4::Multiply(const Vec4& other) const
		{
			return Vec4(x * other.x, y * other.y, z * other.z, w - other.w);
		}

		Vec4 Vec4::Divide(const Vec4& other) const
		{
			return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		float Vec4::Distance(const Maths::Vec4& a, const Maths::Vec4& b)
		{
			return (a - b).GetLength();
		}

		String Vec4::ToString() const
		{
			return "Vec4(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
		}

		// operators

		Vec4 operator+(const Vec4& left, const Vec4& right)
		{
			return left.Add(right);
		}

		Vec4 operator-(const Vec4& left, const Vec4& right)
		{
			return left.Subtract(right);
		}

		Vec4 operator*(const Vec4& left, const Vec4& right)
		{
			return left.Multiply(right);
		}

		Vec4 operator/(const Vec4& left, const Vec4& right)
		{
			return left.Divide(right);
		}

		Vec4 operator+(const Vec4& left, float value)
		{
			return Vec4(left.x + value, left.y + value, left.z + value, left.w + value);
		}

		Vec4 operator-(const Vec4& left, float value)
		{
			return Vec4(left.x - value, left.y - value, left.z - value, left.w - value);
		}

		Vec4 operator*(const Vec4& left, float value)
		{
			return Vec4(left.x * value, left.y * value, left.z * value, left.w * value);
		}

		Vec4 operator/(const Vec4& left, float value)
		{
			return Vec4(left.x / value, left.y / value, left.z / value, left.w / value);
		}

		bool Vec4::operator==(const Vec4& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool Vec4::operator!=(const Vec4& other) const
		{
			return !(*this == other);
		}

		Vec4 Vec4::operator+=(const Vec4& other)
		{
			*this = *this + other;
			return *this;
		}

		Vec4 Vec4::operator-=(const Vec4& other)
		{
			*this = *this - other;
			return *this;
		}

		Vec4 Vec4::operator*=(const Vec4& other)
		{
			*this = *this * other;
			return *this;
		}

		Vec4 Vec4::operator/=(const Vec4& other)
		{
			*this = *this / other;
			return *this;
		}
		
		Vec4 Vec4::operator-() const
		{
			return Vec4(-x, -y, -z, w);
		}

		std::ostream& operator<<(std::ostream& stream, const Vec4& vector)
		{
			stream << vector.ToString();
			return stream;
		}

		Vec4 Vec4::Forward()
		{
			return Vec4(0, 0, -1, 0);
		}

		Vec4 Vec4::Right()
		{
			return Vec4(1, 0, 0, 0);
		}

		Vec4 Vec4::Up()
		{
			return Vec4(0, 1, 0, 0);
		}

	}
}