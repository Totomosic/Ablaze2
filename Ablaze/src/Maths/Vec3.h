#pragma once
#include "Vec2.h"

namespace Ablaze
{
	namespace Maths
	{
		struct AB_API Vec3 : public Object
		{
		public:
			float x;
			float y;
			float z;

		public:
			Vec3(float x, float y, float z);
			Vec3(const Vec2& vector, float z);
			Vec3(float value);
			Vec3();

			float GetX() const { return x; };
			float GetY() const { return y; };
			float GetZ() const { return z; };

			float GetLength() const;
			float GetLengthSqrd() const;
			Vec3 Normalize() const;
			float Dot(const Vec3& other) const;
			Vec3 Cross(const Vec3& other) const;

			Vec2 xy() const;
			Vec2 xz() const;

			Vec3 Add(const Vec3& other) const;
			Vec3 Subtract(const Vec3& other) const;
			Vec3 Multiply(const Vec3& other) const;
			Vec3 Divide(const Vec3& other) const;

			static float Distance(const Maths::Vec3& a, const Maths::Vec3& b);
			static Vec3 Cross(const Vec3& a, const Vec3& b);

			String ToString() const override;

			friend Vec3 operator+(const Vec3& left, const Vec3& right);
			friend Vec3 operator-(const Vec3& left, const Vec3& right);
			friend Vec3 operator*(const Vec3& left, const Vec3& right);
			friend Vec3 operator/(const Vec3& left, const Vec3& right);
			friend Vec3 operator+(const Vec3& left, float value);
			friend Vec3 operator-(const Vec3& left, float value);
			friend Vec3 operator*(const Vec3& left, float value);
			friend Vec3 operator/(const Vec3& left, float value);

			bool operator==(const Vec3& other) const;
			bool operator!=(const Vec3& other) const;

			Vec3 operator+=(const Vec3& other);
			Vec3 operator-=(const Vec3& other);
			Vec3 operator*=(const Vec3& other);
			Vec3 operator/=(const Vec3& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
		};
	}
}