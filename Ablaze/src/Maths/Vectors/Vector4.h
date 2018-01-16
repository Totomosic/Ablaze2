#pragma once
#include "Vector3.h"

namespace Ablaze
{
	namespace Maths
	{

		template<typename T>
		struct AB_API Vector4
		{		
		public:
			T x;
			T y;
			T z;
			T w;

		public:
			Vector4(T x, T y, T z, T w)	
				: x(x), y(y), z(z), w(w)	
			{	
				
			}	
				
			Vector4(const Vector3<T> xyz, T w) : Vector4(xyz.x, xyz.y, xyz.z, w)
			{	
				
			}	
				
			Vector4(Vector3<T> xyz) : Vector4(xyz.x, xyz.y, xyz.z, (T)1)
			{	
				
			}	
				
			Vector4(const Vector2<T>& xy, T z, T w) : Vector4(xy.x, xy.y, z, w)	
			{	
				
			}	
				
			Vector4(const Vector2<T>& xy, T z) : Vector4(xy, z, (T)1)	
			{	
				
			}	
				
			Vector4(const Vector2<T>& xy) : Vector4(xy, (T)0)	
			{	
				
			}	
				
			Vector4(T xyz, T w) : Vector4(xyz, xyz, xyz, w)	
			{	
				
			}	
				
			Vector4(T value) : Vector4(value, value)	
			{	
				
			}	
				
			Vector4() : Vector4((T)0)	
			{	
				
			}	
				
			const T Get(int index) const	
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
					AB_ASSERT(false, "Index out of range");	
				}	
			}	
				
			T& Get(int index)	
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
					AB_ASSERT(false, "Index out of range");	
				}	
			}	
					
			const T operator[](int index) const	
			{	
				return Get(index);	
			}	
						
			T& operator[](int index)	
			{	
				return Get(index);	
			}	
						
			T LengthSqrd() const	
			{	
				return x * x + y * y + z * z + w * w;	
			}	
						
			T Length() const	
			{	
				return sqrt(LengthSqrd());	
			}	
						
			T MagnitudeSqrd() const	
			{	
				return LengthSqrd();	
			}	
						
			T Magnitude() const	
			{	
				return Length();	
			}	
						
			T Dot(const Vector4& other) const	
			{	
				return x * other.x + y * other.y + z * other.z + w * other.w;	
			}	
						
			Vector4 Normalize() const	
			{	
				return *this / Length();	
			}	
						
			Vector4 Add(const Vector4& other) const	
			{	
				return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);	
			}	
						
			Vector4 Add(T other) const	
			{	
				return Vector4(x + other, y + other, z + other, w + other);	
			}	
						
			Vector4 Sub(const Vector4& other) const	
			{	
				return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);	
			}	
						
				Vector4 Sub(T other) const	
			{	
				return Vector4(x - other, y - other, z - other, w - other);	
			}	
						
			Vector4 Mul(const Vector4& other) const	
			{	
				return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);	
			}	
						
			Vector4 Mul(T other) const	
			{	
				return Vector4(x * other, y * other, z * other, w * other);	
			}	
						
			Vector4 Div(const Vector4& other) const	
			{	
				return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);	
			}	
						
			Vector4 Div(T other) const	
			{	
				return Vector4(x / other, y / other, z / other, w / other);	
			}	
						
			friend Vector4 operator+(const Vector4& left, const Vector4& right)
			{	
				return left.Add(right);	
			}	
						
			friend Vector4 operator+(const Vector4& left, T right)
			{	
				return left.Add(right);	
			}	
						
			friend Vector4 operator+(T left, const Vector4& right)
			{	
				return Vector4(left + right.x, left + right.y, left + right.z, left + right.w);	
			}	
						
			friend Vector4 operator-(const Vector4& left, const Vector4& right)
			{	
				return left.Sub(right);	
			}	
						
			friend Vector4 operator-(const Vector4& left, T right)
			{	
				return left.Sub(right);	
			}	
						
			friend Vector4 operator-(T left, const Vector4& right)
			{	
				return Vector4(left - right.x, left - right.y, left - right.z, left - right.w);	
			}	
						
			friend Vector4 operator*(const Vector4& left, const Vector4& right)
			{	
				return left.Mul(right);	
			}	
						
			friend Vector4 operator*(const Vector4& left, T right)
			{	
				return left.Mul(right);	
			}	
						
			friend Vector4 operator*(T left, const Vector4& right)
			{	
				return Vector4(left * right.x, left * right.y, left * right.z, left * right.w);	
			}	
						
			friend Vector4 operator/(const Vector4& left, const Vector4& right)
			{	
				return left.Div(right);	
			}	
						
			friend Vector4 operator/(const Vector4& left, T right)
			{	
				return left.Div(right);	
			}	
						
			friend Vector4 operator/(T left, const Vector4& right)	
			{	
				return Vector4(left / right.x, left / right.y, left / right.z, left / right.w);	
			}	
						
			Vector4& operator+=(const Vector4& other)	
			{	
				*this = *this + other;	
				return *this;	
			}	
						
			Vector4& operator+=(T other)	
			{	
				*this = *this + other;	
				return *this;	
			}	
						
			Vector4& operator-=(const Vector4& other)	
			{	
				*this = *this - other;	
				return *this;	
			}	
						
			Vector4& operator-=(T other)	
			{	
				*this = *this - other;	
				return *this;	
			}	
						
			Vector4& operator*=(const Vector4& other)	
			{	
				*this = *this * other;	
				return *this;	
			}	
						
			Vector4& operator*=(T other)	
			{	
				*this = *this * other;	
				return *this;	
			}	
						
			Vector4& operator/=(const Vector4& other)	
			{	
				*this = *this / other;	
				return *this;	
			}	
						
			Vector4& operator/=(T other)	
			{	
				*this = *this / other;	
				return *this;	
			}	
						
			bool operator==(const Vector4& other) const	
			{	
				return (x == other.x && y == other.y && z == other.z && w == other.w);	
			}	
						
			bool operator!=(const Vector4& other) const	
			{	
				return !(*this == other);	
			}	
						
			Vector4 operator-() const	
			{	
				return Vector4(-x, -y, -z, w);	
			}	
						
			String ToString() const	
			{	
				return "Vector4(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";	
			}	
						
			friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
			{	
				stream << vector.ToString();	
				return stream;	
			}	
						
			Vector3<T> xyz() const	
			{	
				return Vector3<T>(x, y, z);	
			}	
						
			Vector2<T> xy() const	
			{	
				return Vector2<T>(x, y);	
			}	
						
			static T Distance(const Vector4& left, const Vector4& right)	
			{	
				return (left - right).Length();	
			}	
						
			static Vector4 Right()
			{	
				return Vector4((T)1, (T)0, (T)0, (T)0);	
			}	
						
			static Vector4 Up()
			{	
				return Vector4((T)0, (T)1, (T)0, (T)0);	
			}	
						
			static Vector4 Forward()
			{	
				return Vector4((T)0, (T)0, (T)-1, (T)0);	
			}

		};

		typedef Vector4<float> Vector4f;
		typedef Vector4<int> Vector4i;

	}
}