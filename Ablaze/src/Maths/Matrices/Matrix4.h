#pragma once
#include "Maths\Vectors\Vector4.h"

namespace Ablaze
{
	namespace Maths
	{

		template<typename T>
		struct AB_API Matrix4
		{
		public:
			T values[16];

		public:
			Matrix4<T>(T elements[16]) : Matrix4<T>()	
			{	
				for (int i = 0; i < 16; i++)	
				{	
					values[i] = elements[i];	
				}	
			}	
				
			Matrix4<T>(const Vector4<T>& diagonal) : Matrix4<T>()	
			{	
				values[4 * 0 + 0] = diagonal.x;	
				values[4 * 1 + 1] = diagonal.y;	
				values[4 * 2 + 2] = diagonal.z;	
				values[4 * 3 + 3] = diagonal.w;	
			}	
				
			Matrix4<T>(T diagonal) : Matrix4<T>(Vector4<T>(diagonal, diagonal, diagonal, diagonal))	
			{	
				
			}	
				
			Matrix4<T>()	
			{	
				for (int i = 0; i < 16; i++)	
				{	
					values[i] = (T)0;	
				}	
			}	
				
			Vector4<T> Column(int index) const	
			{	
				AB_ASSERT(index < 4, "Index out of range");	
				return Vector4<T>(values[4 * index + 0], values[4 * index + 1], values[4 * index + 2], values[4 * index + 3]);	
			}	
				
			Vector4<T> Row(int index) const	
			{	
				AB_ASSERT(index < 4, "Index out of range");	
				return Vector4<T>(values[4 * 0 + index], values[4 * 1 + index], values[4 * 2 + index], values[4 * 3 + index]);	
			}	
				
			const T Element(int index) const	
			{	
				AB_ASSERT(index < 16, "Index out of range");	
				return values[index];	
			}	
				
			T& Element(int index)	
			{	
				AB_ASSERT(index < 16, "Index out of range");	
				return values[index];	
			}	
				
			const T Element(int row, int col) const	
			{	
				AB_ASSERT(row < 4 && col < 4, "Index out of range");	
				return values[4 * col + row];	
			}	
				
			T& Element(int row, int col)	
			{	
				AB_ASSERT(row < 4 && col < 4, "Index out of range");	
				return values[4 * col + row];	
			}	
				
			const T operator[](int index) const	
			{	
				return Element(index);	
			}	
				
			T& operator[](int index)	
			{	
				return Element(index);	
			}	
				
			void SetColumn(int index, const Vector4<T>& column)	
			{	
				values[4 * index + 0] = column.x;	
				values[4 * index + 1] = column.y;	
				values[4 * index + 2] = column.z;	
				values[4 * index + 3] = column.w;	
			}	
				
			void SetRow(int index, const Vector4<T>& row)	
			{	
				values[4 * 0 + index] = row.x;	
				values[4 * 1 + index] = row.y;	
				values[4 * 2 + index] = row.z;	
				values[4 * 3 + index] = row.w;	
			}	
				
			void SetElement(int row, int col, T value)	
			{	
				values[4 * col + row] = value;	
			}	
				
			Matrix4<T> Inverse() const	
			{	
				T inv[16];	
				T invOut[16];	
				T det;	
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
				
				if (det == (T)0)	
				{	
					AB_ERROR("Matrix could not be inverted");	
					return Identity();	
				}	
					
				det = (T)1 / det;	
				
				for (i = 0; i < 16; i++)	
				{	
					invOut[i] = inv[i] * det;	
				}					
				return Matrix4<T>(invOut);	
			}	
						
			Matrix4<T> operator-() const	
			{	
				return *this * (T)-1;	
			}	
				
			friend Matrix4<T> operator+(const Matrix4<T>& left, const Matrix4<T>& right)
			{	
				Matrix4<T> result;	
				for (int i = 0; i < 16; i++)	
				{	
					result.values[i] = left.values[i] + right.values[i];	
				}	
				return result;	
			}	
				
			friend Matrix4<T> operator+(const Matrix4<T>& left, T right)
			{	
				Matrix4<T> result;	
				for (int i = 0; i < 16; i++)	
				{	
					result.values[i] = left.values[i] + right;	
				}	
				return result;	
			}	
				
			friend Matrix4<T> operator+(T left, const Matrix4<T>& right)
			{	
				return right + left;	
			}	
				
			friend Matrix4<T> operator-(const Matrix4<T>& left, const Matrix4<T>& right)
			{	
				Matrix4<T> result;	
				for (int i = 0; i < 16; i++)	
				{	
					result.values[i] = left.values[i] - right.values[i];	
				}	
				return result;	
			}	
				
			friend Matrix4<T> operator-(const Matrix4<T>& left, T right)
			{	
				Matrix4<T> result;	
				for (int i = 0; i < 16; i++)	
				{	
					result.values[i] = left.values[i] - right;	
				}	
				return result;	
			}	
				
			friend Matrix4<T> operator-(T left, const Matrix4<T>& right)
			{	
				Matrix4<T> result;	
				for (int i = 0; i < 16; i++)	
				{	
					result.values[i] = left - right.values[i];	
				}	
				return result;	
			}	
				
			friend Matrix4<T> operator*(const Matrix4<T>& left, const Matrix4<T>& right)
			{	
				Matrix4<T> result;	
				for (int y = 0; y < 4; y++)	
				{	
					for (int x = 0; x < 4; x++)	
					{	
						T sum = (T)0;	
						for (int e = 0; e < 4; e++)	
						{	
							sum += left.values[x + e * 4] * right.values[e + y * 4];	
						}	
						result.values[x + y * 4] = sum;	
					}	
				}	
				return result;	
			}	
				
			friend Matrix4<T> operator*(const Matrix4<T>& left, T right)
			{	
				Matrix4<T> result;	
				for (int i = 0; i < 16; i++)	
				{	
					result.values[i] = left.values[i] * right;	
				}	
				return result;	
			}	
				
			friend Matrix4<T> operator*(T left, const Matrix4<T>& right)
			{	
				return right * left;	
			}	
				
			friend Vector4<T> operator*(const Matrix4<T>& left, const Vector4<T>& right)
			{	
				T x = left.values[4 * 0 + 0] * right.x + left.values[4 * 1 + 0] * right.y + left.values[4 * 2 + 0] * right.z + left.values[4 * 3 + 0] * right.w;	
				T y = left.values[4 * 0 + 1] * right.x + left.values[4 * 1 + 1] * right.y + left.values[4 * 2 + 1] * right.z + left.values[4 * 3 + 1] * right.w;	
				T z = left.values[4 * 0 + 2] * right.x + left.values[4 * 1 + 2] * right.y + left.values[4 * 2 + 2] * right.z + left.values[4 * 3 + 2] * right.w;	
				T w = left.values[4 * 0 + 3] * right.x + left.values[4 * 1 + 3] * right.y + left.values[4 * 2 + 3] * right.z + left.values[4 * 3 + 3] * right.w;	
				return Vector4<T>(x, y, z, w);	
			}	
				
			friend Vector3<T> operator*(const Matrix4<T>& left, const Vector3<T>& right)
			{	
				Vector4<T> result = left * Vector4<T>(right, (T)1);	
				return result.xyz(); 
			}	
				
			friend Vector2<T> operator*(const Matrix4<T>& left, const Vector2<T>& right)
			{	
				Vector3<T> result = left * Vector3<T>(right, (T)0);
				return result.xy();	
			}	
				
			String ToString() const	
			{	
				String s = " ";	
				String result = "|" + std::to_string(values[0 + 0 * 4]) + s + std::to_string(values[0 + 1 * 4]) + s + std::to_string(values[0 + 2 * 4]) + s + std::to_string(values[0 + 3 * 4]) + "|" + "n"	
				+ "|" + std::to_string(values[1 + 0 * 4]) + s + std::to_string(values[1 + 1 * 4]) + s + std::to_string(values[1 + 2 * 4]) + s + std::to_string(values[1 + 3 * 4]) + "|" + "n"	
				+ "|" + std::to_string(values[2 + 0 * 4]) + s + std::to_string(values[2 + 1 * 4]) + s + std::to_string(values[2 + 2 * 4]) + s + std::to_string(values[2 + 3 * 4]) + "|" + "n"	
				+ "|" + std::to_string(values[3 + 0 * 4]) + s + std::to_string(values[3 + 1 * 4]) + s + std::to_string(values[3 + 2 * 4]) + s + std::to_string(values[3 + 3 * 4]) + "|";	
				return result;	
			}	
				
			friend std::ostream& operator<<(std::ostream& stream, const Matrix4<T>& right)	
			{	
				stream << right.ToString();	
				return stream;	
			}	
				
			static Matrix4<T> Identity()
			{	
				return Matrix4<T>((T)1);	
			}	
				
			static Matrix4<T> Zero()
			{	
				return Matrix4<T>((T)0);	
			}	
				
			static Matrix4<T> FromColumns(const Vector4<T>& c0, const Vector4<T>& c1, const Vector4<T>& c2, const Vector4<T>& c3)
			{	
				Matrix4<T> result;	
				result.SetColumn(0, c0);	
				result.SetColumn(1, c1);	
				result.SetColumn(2, c2);	
				result.SetColumn(3, c3);	
				return result;	
			}	
				
			static Matrix4<T> FromRows(const Vector4<T>& r0, const Vector4<T>& r1, const Vector4<T>& r2, const Vector4<T>& r3)
			{	
				Matrix4<T> result;	
				result.SetRow(0, r0);	
				result.SetRow(1, r1);	
				result.SetRow(2, r2);	
				result.SetRow(3, r3);	
				return result;	
			}	
				
			static Matrix4<T> Orthographic(T left, T right, T bottom, T top, T nearPlane, T farPlane)
			{	
				Matrix4<T> result = Identity();	
				
				result.values[0 + 0 * 4] = (T)2 / (right - left);	
				result.values[1 + 1 * 4] = (T)2 / (top - bottom);	
				result.values[2 + 2 * 4] = (T)-2 / (farPlane - nearPlane);	
				
				result.values[0 + 3 * 4] = -(left + right) / (right - left);	
				result.values[1 + 3 * 4] = -(bottom + top) / (top - bottom);	
				result.values[2 + 3 * 4] = -(farPlane + nearPlane) / (farPlane - nearPlane);	
				
				return result;	
			}	
				
			static Matrix4<T> Perspective(T fov, T aspect, T nearPlane, T farPlane)
			{	
				Matrix4<T> result = Identity();	
				
				float q = (T)1 / (T)tan(0.5f * fov);	
				float a = q / aspect;	
				
				float b = (nearPlane + farPlane) / (nearPlane - farPlane);	
				float c = ((T)2 * nearPlane * farPlane) / (nearPlane - farPlane);	
				
				result.values[0 + 0 * 4] = a;	
				result.values[1 + 1 * 4] = q;	
				result.values[2 + 2 * 4] = b;	
				result.values[3 + 2 * 4] = (T)-1;	
				result.values[2 + 3 * 4] = c;	
				
				return result;	
			}	
				
			static Matrix4<T> Translation(const Vector4<T>& translation)
			{	
				Matrix4<T> result = Identity();	
				result.SetColumn(3, translation);	
				return result;	
			}	
				
			static Matrix4<T> Translation(const Vector3<T>& translation)
			{	
				return Translation(Vector4<T>(translation, (T)1));	
			}	
				
			static Matrix4<T> Translation(T x, T y, T z)
			{	
				return Translation(Vector3<T>(x, y, z));
			}	
				
			static Matrix4<T> Translation(const Vector2<T>& translation)
			{	
				return Translation(Vector3<T>(translation, (T)0));
			}	
				
			static Matrix4<T> Rotation(T angle, const Vector4<T>& axis)
			{	
				return Rotation(angle, axis.xyz());	
			}	
				
			static Matrix4<T> Rotation(T angle, const Vector3<T>& axis)
			{	
				Matrix4<T> result = Identity();	
				
				T c = (T)cos(angle);	
				T s = (T)sin(angle);	
				T omc = (T)1 - c;	
				
				T x = axis.x;	
				T y = axis.y;	
				T z = axis.z;	
				
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
				
			static Matrix4<T> Scale(const Vector4<T>& scale)
			{	
				return Matrix4<T>(scale);	
			}	
				
			static Matrix4<T> Scale(const Vector3<T>& scale)
			{	
				return Scale(Vector4<T>(scale, (T)1));	
			}	
				
			static Matrix4<T> Scale(T x, T y, T z)
			{	
				return Scale(Vector3<T>(x, y, z));	
			}	
				
			static Matrix4<T> Scale(const Vector2<T>& scale)
			{	
				return Scale(Vector3<T>(scale, (T)1));
			}	
				
			static Matrix4<T> Scale(T scale)
			{	
				return Scale(Vector3<T>(scale, scale, scale));	
			}	
				
			static Matrix4<T> InvertX(const Matrix4<T>& mat)
			{	
				Matrix4<T> flipMatrix = Scale((T)-1, (T)1, (T)1);	
				return flipMatrix * mat * flipMatrix;	
			}	
				
			static Matrix4<T> InvertY(const Matrix4<T>& mat)
			{	
				Matrix4<T> flipMatrix = Scale((T)1, (T)-1, (T)1);	
				return flipMatrix * mat * flipMatrix;	
			}	
				
			static Matrix4<T> InvertZ(const Matrix4<T>& mat)	
			{	
				Matrix4<T> flipMatrix = Scale((T)1, (T)1, (T)-1);	
				return flipMatrix * mat * flipMatrix;	
			}

		};

		typedef Matrix4<float> Matrix4f;
		typedef Matrix4<int> Matrix4i;

	}
}