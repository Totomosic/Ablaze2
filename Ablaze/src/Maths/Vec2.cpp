#include "Vec2.h"

namespace Ablaze
{
	namespace Maths
	{
		Vec2::Vec2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vec2::Vec2(float value) : Vec2(value, value)
		{

		}

		Vec2::Vec2() : Vec2(0.0f)
		{

		}

		float Vec2::GetLengthSqrd() const
		{
			return x * x + y * y;
		}

		float Vec2::GetLength() const
		{
			return sqrt(GetLengthSqrd());
		}

		float Vec2::Dot(const Vec2& other) const
		{
			return x * other.x + y * other.y;
		}

		Vec2 Vec2::Normalize() const
		{
			float length = GetLength();
			return Vec2(x / length, y / length);
		}

		Vec2 Vec2::Add(const Vec2& other) const
		{
			return Vec2(x + other.x, y + other.y);
		}

		Vec2 Vec2::Subtract(const Vec2& other) const
		{
			return Vec2(x - other.x, y - other.y);
		}

		Vec2 Vec2::Multiply(const Vec2& other) const
		{
			return Vec2(x * other.x, y * other.y);
		}

		Vec2 Vec2::Divide(const Vec2& other) const
		{
			return Vec2(x / other.x, y / other.y);
		}

		float Vec2::Distance(const Maths::Vec2& a, const Maths::Vec2& b)
		{
			return (a - b).GetLength();
		}

		String Vec2::ToString() const
		{
			return "Vec2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}

		// operators

		Vec2 operator+(const Vec2& left, const Vec2& right)
		{
			return left.Add(right);
		}

		Vec2 operator-(const Vec2& left, const Vec2& right)
		{
			return left.Subtract(right);
		}

		Vec2 operator*(const Vec2& left, const Vec2& right)
		{
			return left.Multiply(right);
		}

		Vec2 operator/(const Vec2& left, const Vec2& right)
		{
			return left.Divide(right);
		}

		Vec2 operator+(const Vec2& left, float value)
		{
			return Vec2(left.x + value, left.y + value);
		}

		Vec2 operator-(const Vec2& left, float value)
		{
			return Vec2(left.x - value, left.y - value);
		}

		Vec2 operator*(const Vec2& left, float value)
		{
			return Vec2(left.x * value, left.y * value);
		}

		Vec2 operator/(const Vec2& left, float value)
		{
			return Vec2(left.x / value, left.y / value);
		}

		bool Vec2::operator==(const Vec2& other) const
		{
			return x == other.x && y == other.y;
		}

		bool Vec2::operator!=(const Vec2& other) const
		{
			return !(*this == other);
		}

		Vec2 Vec2::operator+=(const Vec2& other)
		{
			*this = *this + other;
			return *this;
		}

		Vec2 Vec2::operator-=(const Vec2& other)
		{
			*this = *this - other;
			return *this;
		}

		Vec2 Vec2::operator*=(const Vec2& other)
		{
			*this = *this * other;
			return *this;
		}

		Vec2 Vec2::operator/=(const Vec2& other)
		{
			*this = *this / other;
			return *this;
		}

		Vec2 Vec2::operator-() const
		{
			return Vec2(-x, -y);
		}

		std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
		{
			stream << vector.ToString();
			return stream;
		}

		Vec2 Vec2::Right()
		{
			return Vec2(1, 0);
		}

		Vec2 Vec2::Up()
		{
			return Vec2(0, 1);
		}

	}
}