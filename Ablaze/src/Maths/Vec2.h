#pragma once
#include "Object.h"

namespace Ablaze
{

	class JSONwriter;
	class JSONnode;

	namespace Maths
	{
		struct AB_API Vec2
		{
		public:
			float x;
			float y;

		public:
			Vec2(float x, float y);
			Vec2(float value);
			Vec2();

			float GetX() const { return x; };
			float GetY() const { return y; };

			float GetLength() const;
			float GetLengthSqrd() const;
			Vec2 Normalize() const;
			float Dot(const Vec2& other) const;

			Vec2 Add(const Vec2& other) const;
			Vec2 Subtract(const Vec2& other) const;
			Vec2 Multiply(const Vec2& other) const;
			Vec2 Divide(const Vec2& other) const;

			String ToString() const;
			void Serialize(JSONwriter& writer) const;

			friend Vec2 operator+(const Vec2& left, const Vec2& right);
			friend Vec2 operator-(const Vec2& left, const Vec2& right);
			friend Vec2 operator*(const Vec2& left, const Vec2& right);
			friend Vec2 operator/(const Vec2& left, const Vec2& right);
			friend Vec2 operator+(const Vec2& left, float value);
			friend Vec2 operator-(const Vec2& left, float value);
			friend Vec2 operator*(const Vec2& left, float value);
			friend Vec2 operator/(const Vec2& left, float value);

			bool operator==(const Vec2& other) const;
			bool operator!=(const Vec2& other) const;

			Vec2 operator+=(const Vec2& other);
			Vec2 operator-=(const Vec2& other);
			Vec2 operator*=(const Vec2& other);
			Vec2 operator/=(const Vec2& other);
			Vec2 operator-() const;

			friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);

		public:
			static float Distance(const Vec2& a, const Vec2& b);
			static Vec2 Right();
			static Vec2 Up();

			static Vec2 Deserialize(JSONnode& node);

		};
	}
}