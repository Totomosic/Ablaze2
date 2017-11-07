#pragma once
#include "Vec3.h"

namespace Ablaze
{
	namespace Maths
	{
		struct AB_API Vec4
		{
		public:
			float x;
			float y;
			float z;
			float w;

		public:
			Vec4(float x, float y, float z, float w);
			Vec4(const Vec3& vector, float w);
			Vec4(const Vec2& vector, float z, float w);
			Vec4(float xyz, float w);
			Vec4(float value);
			Vec4() = default;

			float GetX() const { return x; };
			float GetY() const { return y; };
			float GetZ() const { return z; };
			float GetW() const { return w; };
			float Get(int index) const;

			Vec2 xy() const;
			Vec3 xyz() const;

			float GetLength() const;
			float GetLengthSqrd() const;
			Vec4 Normalize() const;
			float Dot(const Vec4& other) const;

			Vec4 Add(const Vec4& other) const;
			Vec4 Subtract(const Vec4& other) const;
			Vec4 Multiply(const Vec4& other) const;
			Vec4 Divide(const Vec4& other) const;

			static float Distance(const Vec4& a, const Vec4& b);

			String ToString() const;

			friend Vec4 operator+(const Vec4& left, const Vec4& right);
			friend Vec4 operator-(const Vec4& left, const Vec4& right);
			friend Vec4 operator*(const Vec4& left, const Vec4& right);
			friend Vec4 operator/(const Vec4& left, const Vec4& right);
			friend Vec4 operator+(const Vec4& left, float value);
			friend Vec4 operator-(const Vec4& left, float value);
			friend Vec4 operator*(const Vec4& left, float value);
			friend Vec4 operator/(const Vec4& left, float value);

			bool operator==(const Vec4& other) const;
			bool operator!=(const Vec4& other) const;

			Vec4 operator+=(const Vec4& other);
			Vec4 operator-=(const Vec4& other);
			Vec4 operator*=(const Vec4& other);
			Vec4 operator/=(const Vec4& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
		};
	}
}