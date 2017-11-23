#pragma once
#include "Vec4.h"

// Transformation happen from RIGHT TO LEFT
// Example:
// Mat4::translation(Vec3(5, 5, 5)) * Mat4::rotation(M_PI / 4.0f, Vec3(0, 0, 1));
// Rotates by 45 degrees around the z-axis then translates to position (5, 5, 5)

namespace Ablaze
{
	namespace Maths
	{

		struct AB_API Mat4
		{
		public:
			float values[4 * 4];

		public:
			Mat4();
			Mat4(float diagonal);
			Mat4(float values[16]);

			Vec4 GetColumn(int col) const;
			Vec4 GetRow(int row) const;
			float GetElement(int row, int col) const;

			void SetColumn(int col, const Vec4& column);
			void SetRow(int row, const Vec4& rowVal);
			void SetElement(int row, int col, float value);

			Mat4 Multiply(const Mat4& other) const;
			Vec4 Multiply(const Vec4& other) const;
			Vec3 Multiply(const Vec3& other) const;
			Mat4 Inverse() const;

			String ToString() const;
			void Serialize(JSONwriter& writer) const;
			
			static Mat4 FromRows(const Vec4& r1, const Vec4& r2, const Vec4& r3, const Vec4& r4);
			static Mat4 FromCols(const Vec4& c1, const Vec4& c2, const Vec4& c3, const Vec4& c4);

			static Mat4 Identity();
			static Mat4 Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
			static Mat4 Perspective(float fov, float aspect, float nearPlane, float farPlane);

			static Mat4 Translation(const Vec3& translation);
			static Mat4 Translation(float x, float y, float z);
			static Mat4 Rotation(double angle, const Vec3& axis);
			static Mat4 Scale(const Vec3& scale);
			static Mat4 Scale(float x, float y, float z);
			static Mat4 Scale(float scale);
			static Mat4 InvertX(const Maths::Mat4& other);
			static Mat4 InvertY(const Maths::Mat4& other);
			static Mat4 InvertZ(const Maths::Mat4& other);

			friend Mat4 operator*(const Mat4& left, const Mat4& right);
			friend Vec4 operator*(const Mat4& left, const Vec4& right);
			friend Vec3 operator*(const Mat4& left, const Vec3& right);
			Mat4& operator*=(const Mat4& right);

			friend std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);

		};

	}
}