#pragma once
#include "Vector2.h"

namespace Ablaze
{
	namespace Maths
	{
		
		template<typename T>
		struct AB_API Vector3
		{
		public:
			T x;
			T y;
			T z;

		public:
			Vector3(T x, T y, T z)	
				: x(x), y(y), z(z)	
			{	
				
			}	
				
			Vector3(const Vector2<T>& xy, T z) : Vector3(xy.x, xy.y, z)
			{	
				
			}	
				
			Vector3(const Vector2<T>& xy) : Vector3(xy.x, xy.y, (T)0)
			{	
				
			}	
				
			Vector3(T value) : Vector3(value, value)	
			{	
				
			}	
				
			Vector3() : Vector3((T)0)	
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
				return x * x + y * y + z * z;	
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
						
			T Dot(const Vector3<T>& other) const	
			{	
				return x * other.x + y * other.y + z * other.z;	
			}	
						
			Vector3<T> Cross(const Vector3<T>& other) const	
			{	
				return Cross(*this, other);	
			}	
						
			Vector3<T> Normalize() const	
			{	
				return *this / Length();	
			}	
						
			Vector3<T> Add(const Vector3<T>& other) const	
			{	
				return Vector3<T>(x + other.x, y + other.y, z + other.z);	
			}	
						
			Vector3<T> Add(T other) const	
			{	
				return Vector3<T>(x + other, y + other, z + other);	
			}	
						
			Vector3<T> Sub(const Vector3<T>& other) const	
			{	
				return Vector3<T>(x - other.x, y - other.y, z - other.z);	
			}	
						
			Vector3<T> Sub(T other) const	
			{	
				return Vector3<T>(x - other, y - other, z - other);	
			}	
						
			Vector3<T> Mul(const Vector3<T>& other) const	
			{	
				return Vector3<T>(x * other.x, y * other.y, z * other.z);	
			}	
						
			Vector3<T> Mul(T other) const	
			{	
				return Vector3<T>(x * other, y * other, z * other);	
			}	
						
			Vector3<T> Div(const Vector3<T>& other) const	
			{	
				return Vector3<T>(x / other.x, y / other.y, z / other.z);	
			}	
						
			Vector3<T> Div(T other) const	
			{	
				return Vector3<T>(x / other, y / other, z / other);	
			}	
						
			friend Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
			{	
				return left.Add(right);	
			}	
						
			friend Vector3<T> operator+(const Vector3<T>& left, T right)
			{	
				return left.Add(right);	
			}	
						
			friend Vector3<T> operator+(T left, const Vector3<T>& right)
			{	
				return Vector3<T>(left + right.x, left + right.y, left + right.z);	
			}	
						
			friend Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
			{	
				return left.Sub(right);	
			}	
						
			friend Vector3<T> operator-(const Vector3<T>& left, T right)
			{	
				return left.Sub(right);	
			}	
						
			friend Vector3<T> operator-(T left, const Vector3<T>& right)
			{	
				return Vector3<T>(left - right.x, left - right.y, left - right.z);	
			}	
						
			friend Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right)
			{	
				return left.Mul(right);	
			}	
						
			friend Vector3<T> operator*(const Vector3<T>& left, T right)
			{	
				return left.Mul(right);	
			}	
						
			friend Vector3<T> operator*(T left, const Vector3<T>& right)
			{	
				return Vector3<T>(left * right.x, left * right.y, left * right.z);	
			}	
						
			friend Vector3<T> operator/(const Vector3<T>& left, const Vector3<T>& right)
			{	
				return left.Div(right);	
			}	
						
			friend Vector3<T> operator/(const Vector3<T>& left, T right)
			{	
				return left.Div(right);	
			}	
						
			friend Vector3<T> operator/(T left, const Vector3<T>& right)
			{	
				return Vector3<T>(left / right.x, left / right.y, left / right.z);	
			}	
						
			Vector3<T>& operator+=(const Vector3<T>& other)	
			{	
				*this = *this + other;	
				return *this;	
			}	
						
			Vector3<T>& operator+=(T other)	
			{	
				*this = *this + other;	
				return *this;	
			}	
						
			Vector3<T>& operator-=(const Vector3<T>& other)	
			{	
				*this = *this - other;	
				return *this;	
			}	
						
			Vector3<T>& operator-=(T other)	
			{	
				*this = *this - other;	
				return *this;	
			}	
						
			Vector3<T>& operator*=(const Vector3<T>& other)	
			{	
				*this = *this * other;	
				return *this;	
			}	
						
			Vector3<T>& operator*=(T other)	
			{	
				*this = *this * other;	
				return *this;	
			}	
						
			Vector3<T>& operator/=(const Vector3<T>& other)	
			{	
				*this = *this / other;	
				return *this;	
			}	
						
			Vector3<T>& operator/=(T other)	
			{	
				*this = *this / other;	
				return *this;	
			}	
						
			bool operator==(const Vector3<T>& other) const	
			{	
				return (x == other.x && y == other.y && z == other.z);	
			}	
						
			bool operator!=(const Vector3<T>& other) const	
			{	
				return !(*this == other);	
			}	
						
			Vector3<T> operator-() const	
			{	
				return Vector3<T>(-x, -y, -z);	
			}	
						
			String ToString() const	
			{	
				return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";	
			}	
						
			friend std::ostream& operator<<(std::ostream& stream, const Vector3<T>& vector)	
			{	
				stream << vector.ToString();	
				return stream;	
			}	
						
			Vector2<T> xy() const	
			{	
				return Vector2<T>(x, y);
			}	
						
			Vector2<T> xz() const
			{	
				return Vector2<T>(x, z);
			}	
						
			static Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right)
			{	
				return Vector3<T>(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);	
			}	
						
			static T Distance(const Vector3<T>& left, const Vector3<T>& right)
			{	
				return (left - right).Length();	
			}	
						
			static void OrthoNormalize(Vector3<T>* normal, Vector3<T>* tangent)
			{	
				*normal = normal->Normalize();	
				Vector3<T> v = Cross(*normal, *tangent);	
				v = v.Normalize();	
				*tangent = Cross(v, *normal);	
			}	

			static Vector3<T> SmoothDamp(const Vector3<T>& current, const Vector3<T>& end, Vector3<T>* currentVelocity, T smoothTime, T deltaTime, T maxSpeed = std::numeric_limits<T>::infinity())
			{
				smoothTime = max((T)0.0001, smoothTime);
				float num = 2.0f / smoothTime;
				float num2 = num * deltaTime;
				float d = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
				Vector3<T> vector = current - end;
				Vector3<T> vector2 = end;
				float maxLength = maxSpeed * smoothTime;
				if (vector.Length() > maxSpeed)
				{
					vector = vector.Normalize() * maxSpeed;
				}
				Vector3<T> target = current - vector;
				Vector3<T> vector3 = (*currentVelocity + num * vector) * deltaTime;
				*currentVelocity = (*currentVelocity - num * vector3) * d;
				Vector3<T> vector4 = target + (vector + vector3) * d;
				if ((vector2 - current).Dot(vector4 - vector2) > 0.0f)
				{
					vector4 = vector2;
					*currentVelocity = (vector4 - vector2) / deltaTime;
				}
				return vector4;
			}
						
			static Vector3<T> Right()
			{	
				return Vector3<T>((T)1, (T)0, (T)0);	
			}	
						
			static Vector3<T> Up()
			{	
				return Vector3<T>((T)0, (T)1, (T)0);	
			}	
						
			static Vector3<T> Forward()	
			{	
				return Vector3<T>((T)0, (T)0, (T)-1);	
			}

		};

		typedef Vector3<float> Vector3f;
		typedef Vector3<int> Vector3i;

	}
}