#include "Mat4.h"
#include "Logging.h"

namespace Ablaze
{
	namespace Maths
	{
		Mat4::Mat4() : Object()
		{
			// instantiate every value to 0
			for (int i = 0; i < 4 * 4; i++)
			{
				values[i] = 0.0f;
			}
		}

		Mat4::Mat4(float vals[16]) : Object()
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				values[i] = vals[i];
			}
		}

		Mat4::Mat4(float diagonal) : Mat4::Mat4()
		{
			values[0 + 0 * 4] = diagonal;
			values[1 + 1 * 4] = diagonal;
			values[2 + 2 * 4] = diagonal;
			values[3 + 3 * 4] = diagonal;
		}

		Vec4 Mat4::GetColumn(int col) const
		{
			return Maths::Vec4(values[0 + col * 4], values[1 + col * 4], values[2 + col * 4], values[3 + col * 4]);
		}

		Vec4 Mat4::GetRow(int row) const
		{
			return Maths::Vec4(values[row + 0 * 4], values[row + 1 * 4], values[row + 2 * 4], values[row + 3 * 4]);
		}

		float Mat4::GetElement(int row, int col) const
		{
			return values[row + col * 4];
		}

		void Mat4::SetColumn(int col, const Vec4& colVal)
		{
			SetElement(0, col, colVal.x);
			SetElement(1, col, colVal.y);
			SetElement(2, col, colVal.z);
			SetElement(3, col, colVal.w);
		}

		void Mat4::SetRow(int row, const Vec4& rowVal)
		{
			SetElement(row, 0, rowVal.x);
			SetElement(row, 1, rowVal.y);
			SetElement(row, 2, rowVal.z);
			SetElement(row, 3, rowVal.w);
		}

		void Mat4::SetElement(int row, int col, float value)
		{
			values[row + col * 4] = value;
		}

		Mat4 Mat4::FromRows(const Vec4& r1, const Vec4& r2, const Vec4& r3, const Vec4& r4)
		{
			Mat4 m;
			m.SetRow(0, r1);
			m.SetRow(1, r2);
			m.SetRow(2, r3);
			m.SetRow(3, r4);
			return m;
		}

		Mat4 Mat4::FromCols(const Vec4& c1, const Vec4& c2, const Vec4& c3, const Vec4& c4)
		{
			Mat4 m;
			m.SetColumn(0, c1);
			m.SetColumn(1, c2);
			m.SetColumn(2, c3);
			m.SetColumn(3, c4);
			return m;
		}

		std::string Mat4::ToString() const
		{
			std::string s = " ";
			std::string result = "|" + std::to_string(values[0 + 0 * 4]) + s + std::to_string(values[0 + 1 * 4]) + s + std::to_string(values[0 + 2 * 4]) + s + std::to_string(values[0 + 3 * 4]) + "|" + "\n"
				+ "|" + std::to_string(values[1 + 0 * 4]) + s + std::to_string(values[1 + 1 * 4]) + s + std::to_string(values[1 + 2 * 4]) + s + std::to_string(values[1 + 3 * 4]) + "|" + "\n"
				+ "|" + std::to_string(values[2 + 0 * 4]) + s + std::to_string(values[2 + 1 * 4]) + s + std::to_string(values[2 + 2 * 4]) + s + std::to_string(values[2 + 3 * 4]) + "|" + "\n"
				+ "|" + std::to_string(values[3 + 0 * 4]) + s + std::to_string(values[3 + 1 * 4]) + s + std::to_string(values[3 + 2 * 4]) + s + std::to_string(values[3 + 3 * 4]) + "|";
			return result;
		}

		Mat4 Mat4::Identity()
		{
			return Mat4(1.0f);
		}

		Mat4 Mat4::Multiply(const Mat4& other) const
		{
			float data[16];
			Mat4 result;
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += values[x + e * 4] * other.values[e + y * 4];
					}
					data[x + y * 4] = sum;
				}
			}
			memcpy(result.values, data, 16 * sizeof(float));
			return result;
		}

		Vec4 Mat4::Multiply(const Vec4& other) const
		{
			return Maths::Vec4(values[0 + 0 * 4] * other.x + values[0 + 1 * 4] * other.y + values[0 + 2 * 4] * other.z + values[0 + 3 * 4] * other.w, values[1 + 0 * 4] * other.x + values[1 + 1 * 4] * other.y + values[1 + 2 * 4] * other.z + values[1 + 3 * 4] * other.w, values[2 + 0 * 4] * other.x + values[2 + 1 * 4] * other.y + values[2 + 2 * 4] * other.z + values[2 + 3 * 4] * other.w, values[3 + 0 * 4] * other.x + values[3 + 1 * 4] * other.y + values[3 + 2 * 4] * other.z + values[3 + 3 * 4] * other.w);
		}

		Vec3 Mat4::Multiply(const Vec3& other) const
		{
			return Multiply(Maths::Vec4(other, 1)).xyz();
		}

		Mat4 Mat4::Inverse() const
		{
			double inv[16], det;
			float invOut[16];
			int i;

			inv[0] = values[5] * values[10] * values[15] -
				values[5] * values[11] * values[14] -
				values[9] * values[6] * values[15] +
				values[9] * values[7] * values[14] +
				values[13] * values[6] * values[11] -
				values[13] * values[7] * values[10];

			inv[4] = -values[4] * values[10] * values[15] +
				values[4] * values[11] * values[14] +
				values[8] * values[6] * values[15] -
				values[8] * values[7] * values[14] -
				values[12] * values[6] * values[11] +
				values[12] * values[7] * values[10];

			inv[8] = values[4] * values[9] * values[15] -
				values[4] * values[11] * values[13] -
				values[8] * values[5] * values[15] +
				values[8] * values[7] * values[13] +
				values[12] * values[5] * values[11] -
				values[12] * values[7] * values[9];

			inv[12] = -values[4] * values[9] * values[14] +
				values[4] * values[10] * values[13] +
				values[8] * values[5] * values[14] -
				values[8] * values[6] * values[13] -
				values[12] * values[5] * values[10] +
				values[12] * values[6] * values[9];

			inv[1] = -values[1] * values[10] * values[15] +
				values[1] * values[11] * values[14] +
				values[9] * values[2] * values[15] -
				values[9] * values[3] * values[14] -
				values[13] * values[2] * values[11] +
				values[13] * values[3] * values[10];

			inv[5] = values[0] * values[10] * values[15] -
				values[0] * values[11] * values[14] -
				values[8] * values[2] * values[15] +
				values[8] * values[3] * values[14] +
				values[12] * values[2] * values[11] -
				values[12] * values[3] * values[10];

			inv[9] = -values[0] * values[9] * values[15] +
				values[0] * values[11] * values[13] +
				values[8] * values[1] * values[15] -
				values[8] * values[3] * values[13] -
				values[12] * values[1] * values[11] +
				values[12] * values[3] * values[9];

			inv[13] = values[0] * values[9] * values[14] -
				values[0] * values[10] * values[13] -
				values[8] * values[1] * values[14] +
				values[8] * values[2] * values[13] +
				values[12] * values[1] * values[10] -
				values[12] * values[2] * values[9];

			inv[2] = values[1] * values[6] * values[15] -
				values[1] * values[7] * values[14] -
				values[5] * values[2] * values[15] +
				values[5] * values[3] * values[14] +
				values[13] * values[2] * values[7] -
				values[13] * values[3] * values[6];

			inv[6] = -values[0] * values[6] * values[15] +
				values[0] * values[7] * values[14] +
				values[4] * values[2] * values[15] -
				values[4] * values[3] * values[14] -
				values[12] * values[2] * values[7] +
				values[12] * values[3] * values[6];

			inv[10] = values[0] * values[5] * values[15] -
				values[0] * values[7] * values[13] -
				values[4] * values[1] * values[15] +
				values[4] * values[3] * values[13] +
				values[12] * values[1] * values[7] -
				values[12] * values[3] * values[5];

			inv[14] = -values[0] * values[5] * values[14] +
				values[0] * values[6] * values[13] +
				values[4] * values[1] * values[14] -
				values[4] * values[2] * values[13] -
				values[12] * values[1] * values[6] +
				values[12] * values[2] * values[5];

			inv[3] = -values[1] * values[6] * values[11] +
				values[1] * values[7] * values[10] +
				values[5] * values[2] * values[11] -
				values[5] * values[3] * values[10] -
				values[9] * values[2] * values[7] +
				values[9] * values[3] * values[6];

			inv[7] = values[0] * values[6] * values[11] -
				values[0] * values[7] * values[10] -
				values[4] * values[2] * values[11] +
				values[4] * values[3] * values[10] +
				values[8] * values[2] * values[7] -
				values[8] * values[3] * values[6];

			inv[11] = -values[0] * values[5] * values[11] +
				values[0] * values[7] * values[9] +
				values[4] * values[1] * values[11] -
				values[4] * values[3] * values[9] -
				values[8] * values[1] * values[7] +
				values[8] * values[3] * values[5];

			inv[15] = values[0] * values[5] * values[10] -
				values[0] * values[6] * values[9] -
				values[4] * values[1] * values[10] +
				values[4] * values[2] * values[9] +
				values[8] * values[1] * values[6] -
				values[8] * values[2] * values[5];

			det = values[0] * inv[0] + values[1] * inv[4] + values[2] * inv[8] + values[3] * inv[12];

			if (det == 0)
			{
				AB_ERROR("Matrix could not be inverted");
				return Maths::Mat4::Identity();
			}

			det = 1.0 / det;

			for (i = 0; i < 16; i++)
				invOut[i] = inv[i] * det;

			return Mat4(invOut);
		}

		Mat4 operator*(const Mat4& left, const Mat4& right)
		{
			return left.Multiply(right);
		}

		Vec4 operator*(const Mat4& left, const Vec4& right)
		{
			return left.Multiply(right);
		}

		Vec3 operator*(const Mat4& left, const Vec3& right)
		{
			return left.Multiply(right);
		}

		Mat4& Mat4::operator*=(const Mat4& right)
		{
			*this = *this * right;
			return *this;
		}

		Mat4 Mat4::Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
		{
			Mat4 result(1.0f);

			result.values[0 + 0 * 4] = 2.0f / (right - left);
			result.values[1 + 1 * 4] = 2.0f / (top - bottom);
			result.values[2 + 2 * 4] = -2.0f / (farPlane - nearPlane);

			result.values[0 + 3 * 4] = -(left + right) / (right - left);
			result.values[1 + 3 * 4] = -(bottom + top) / (top - bottom);
			result.values[2 + 3 * 4] = -(farPlane + nearPlane) / (farPlane - nearPlane);

			return result;
		}

		Mat4 Mat4::Perspective(float fov, float aspect, float nearPlane, float farPlane)
		{
			Mat4 result(1.0f);

			float q = 1.0f / tan(0.5f * fov);
			float a = q / aspect;

			float b = (nearPlane + farPlane) / (nearPlane - farPlane);
			float c = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);

			result.values[0 + 0 * 4] = a;
			result.values[1 + 1 * 4] = q;
			result.values[2 + 2 * 4] = b;
			result.values[3 + 2 * 4] = -1.0f;
			result.values[2 + 3 * 4] = c;

			return result;
		}

		Mat4 Mat4::Translation(const Vec3& translation)
		{
			Mat4 result(1.0f);
			result.values[0 + 3 * 4] = translation.x;
			result.values[1 + 3 * 4] = translation.y;
			result.values[2 + 3 * 4] = translation.z;
			return result;
		}

		Mat4 Mat4::Translation(float x, float y, float z)
		{
			return Translation(Maths::Vec3(x, y, z));
		}

		Mat4 Mat4::Rotation(double angle, const Vec3& axis)
		{
			Mat4 result(1.0f);

			double c = cos(angle);
			double s = sin(angle);
			double omc = 1.0 - c;

			double x = axis.x;
			double y = axis.y;
			double z = axis.z;

			result.values[0 + 0 * 4] = x * omc + c;
			result.values[1 + 0 * 4] = y * x * omc + z * s;
			result.values[2 + 0 * 4] = x * z * omc - y * s;

			result.values[0 + 1 * 4] = x * y * omc - z * s;
			result.values[1 + 1 * 4] = y * omc + c;
			result.values[2 + 1 * 4] = y * z * omc + x * s;

			result.values[0 + 2 * 4] = x * z * omc + y * s;
			result.values[1 + 2 * 4] = y * z * omc - x * s;
			result.values[2 + 2 * 4] = z * omc + c;

			return result;
		}

		Mat4 Mat4::Scale(const Vec3& scale)
		{
			Mat4 result(1.0f);
			result.values[0 + 0 * 4] = scale.x;
			result.values[1 + 1 * 4] = scale.y;
			result.values[2 + 2 * 4] = scale.z;
			return result;
		}

		Mat4 Mat4::Scale(float x, float y, float z)
		{
			return Scale(Maths::Vec3(x, y, z));
		}

		Mat4 Mat4::Scale(float scale)
		{
			return Mat4::Scale(Maths::Vec3(scale));
		}

		Mat4 Mat4::InvertX(const Maths::Mat4& other)
		{
			Mat4 flipMatrix = Scale(-1.f, 1.f, 1.f);
			return flipMatrix * other * flipMatrix;
		}

		Mat4 Mat4::InvertY(const Maths::Mat4& other)
		{
			Mat4 flipMatrix = Scale(1.f, -1.f, 1.f);
			return flipMatrix * other * flipMatrix;
		}

		Mat4 Mat4::InvertZ(const Maths::Mat4& other)
		{
			Mat4 flipMatrix = Scale(1.f, 1.f, -1.f);
			return flipMatrix * other * flipMatrix;
		}

		std::ostream& operator<<(std::ostream& stream, const Mat4& matrix)
		{
			const char* s = " ";
			stream << matrix.ToString();
			return stream;
		}
	}
}