#pragma once
#include "Vectors\__Vectors__.h"

namespace Ablaze
{

	class JSONwriter;
	class JSONnode;

	namespace Maths
	{

		struct AB_API Matrix4f
		{
		public:
			float values[4 * 4];

		public:
			Matrix4f();
			Matrix4f(float diagonal);
			Matrix4f(float values[16]);

			Vector4f GetColumn(int col) const;
			Vector4f GetRow(int row) const;
			float GetElement(int row, int col) const;

			void SetColumn(int col, const Vector4f& column);
			void SetRow(int row, const Vector4f& rowVal);
			void SetElement(int row, int col, float value);

			Matrix4f Multiply(const Matrix4f& other) const;
			Vector4f Multiply(const Vector4f& other) const;
			Vector3f Multiply(const Vector3f& other) const;
			Matrix4f Inverse() const;

			String ToString() const;
			void Serialize(JSONwriter& writer) const;
			
		public:
			static Matrix4f FromRows(const Vector4f& r1, const Vector4f& r2, const Vector4f& r3, const Vector4f& r4);
			static Matrix4f FromCols(const Vector4f& c1, const Vector4f& c2, const Vector4f& c3, const Vector4f& c4);

			static Matrix4f Identity();
			static Matrix4f Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
			static Matrix4f Perspective(float fov, float aspect, float nearPlane, float farPlane);

			static Matrix4f Translation(const Vector3f& translation);
			static Matrix4f Translation(float x, float y, float z);
			static Matrix4f Rotation(double angle, const Vector3f& axis);
			static Matrix4f Scale(const Vector3f& scale);
			static Matrix4f Scale(float x, float y, float z);
			static Matrix4f Scale(float scale);
			static Matrix4f InvertX(const Maths::Matrix4f& other);
			static Matrix4f InvertY(const Maths::Matrix4f& other);
			static Matrix4f InvertZ(const Maths::Matrix4f& other);

			friend Matrix4f operator*(const Matrix4f& left, const Matrix4f& right);
			friend Vector4f operator*(const Matrix4f& left, const Vector4f& right);
			friend Vector3f operator*(const Matrix4f& left, const Vector3f& right);
			Matrix4f& operator*=(const Matrix4f& right);

			friend std::ostream& operator<<(std::ostream& stream, const Matrix4f& matrix);

		};

	}
}