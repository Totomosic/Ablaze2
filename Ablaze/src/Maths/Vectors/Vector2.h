#pragma once
#include "Object.h"
#include "Logging.h"

namespace Ablaze
{
	namespace Maths
	{

		template<typename T>
		struct AB_API Vector2
		{
		public:
			T x;
			T y;

		public:
			Vector2(T x, T y)	
				: x(x), y(y)	
			{	
				
			}	
				
			Vector2(T value) : Vector2(value, value)	
			{	
				
			}	
				
			Vector2() : Vector2((T)0)	
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
				return x * x + y * y;	
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
						
			T Dot(const Vector2<T>& other) const	
			{	
				return x * other.x + y * other.y;	
			}	
						
			Vector2<T> Normalize() const	
			{	
				return (*this) / Length();	
			}	
						
			Vector2<T> Add(const Vector2<T>& other) const	
			{	
				return Vector2<T>(x + other.x, y + other.y);	
			}	
						
			Vector2<T> Add(T other) const	
			{	
				return Vector2<T>(x + other, y + other);	
			}	
						
			Vector2<T> Sub(const Vector2<T>& other) const	
			{	
				return Vector2<T>(x - other.x, y - other.y);	
			}	
						
			Vector2<T> Sub(T other) const	
			{	
				return Vector2<T>(x - other, y - other);	
			}	
						
			Vector2<T> Mul(const Vector2<T>& other) const	
			{	
				return Vector2<T>(x * other.x, y * other.y);	
			}	
						
			Vector2<T> Mul(T other) const	
			{	
				return Vector2<T>(x * other, y * other);	
			}	
						
			Vector2<T> Div(const Vector2<T>& other) const	
			{	
				return Vector2<T>(x / other.x, y / other.y);	
			}	
						
			Vector2<T> Div(T other) const	
			{	
				return Vector2<T>(x / other, y / other);	
			}	
						
			friend Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
			{	
				return left.Add(right);	
			}	
						
			friend Vector2<T> operator+(const Vector2<T>& left, T right)
			{	
				return left.Add(right);	
			}	
						
			friend Vector2<T> operator+(T left, const Vector2<T>& right)
			{	
				return Vector2<T>(left + right.x, left + right.y);	
			}	
						
			friend Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
			{	
				return left.Sub(right);	
			}	
						
			friend Vector2<T> operator-(const Vector2<T>& left, T right)
			{	
				return left.Sub(right);	
			}	
						
			friend Vector2<T> operator-(T left, const Vector2<T>& right)
			{	
				return Vector2<T>(left - right.x, left - right.y);	
			}	
						
			friend Vector2<T> operator*(const Vector2<T>& left, const Vector2<T>& right)
			{	
				return left.Mul(right);	
			}	
						
			friend Vector2<T> operator*(const Vector2<T>& left, T right)
			{	
				return left.Mul(right);	
			}	
						
			friend Vector2<T> operator*(T left, const Vector2<T>& right)
			{	
				return Vector2<T>(left * right.x, left * right.y);	
			}	
						
			friend Vector2<T> operator/(const Vector2<T>& left, const Vector2<T>& right)
			{	
				return left.Div(right);	
			}	
						
			friend Vector2<T> operator/(const Vector2<T>& left, T right)
			{	
				return left.Div(right);	
			}	
						
			friend Vector2<T> operator/(T left, const Vector2<T>& right)
			{	
				return Vector2<T>(left / right.x, left / right.y);	
			}	
						
			Vector2<T>& operator+=(const Vector2<T>& other)	
			{	
				*this = *this + other;	
				return *this;	
			}	
						
			Vector2<T>& operator+=(T other)	
			{	
				*this = *this + other;	
				return *this;	
			}	
						
			Vector2<T>& operator-=(const Vector2<T>& other)	
			{	
				*this = *this - other;	
				return *this;	
			}	
						
			Vector2<T>& operator-=(T other)	
			{	
				*this = *this - other;	
				return *this;	
			}	
						
			Vector2<T>& operator*=(const Vector2<T>& other)	
			{	
				*this = *this * other;	
				return *this;	
			}	
						
			Vector2<T>& operator*=(T other)	
			{	
				*this = *this * other;	
				return *this;	
			}	
						
			Vector2<T>& operator/=(const Vector2<T>& other)	
			{	
				*this = *this / other;	
				return *this;	
			}	
						
			Vector2<T>& operator/=(T other)	
			{	
				*this = *this / other;	
				return *this;	
			}	
						
			bool operator==(const Vector2<T>& other) const	
			{	
				return (x == other.x && y == other.y);	
			}	
						
			bool operator!=(const Vector2<T>& other) const	
			{	
				return !(*this == other);	
			}	
						
			Vector2<T> operator-() const	
			{	
				return Vector2<T>(-x, -y);	
			}	
						
			String ToString() const	
			{	
				return "Vector2(" + std::to_string(x) + ", " + std::to_string(y) + ")";	
			}	
						
			friend std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector)
			{	
				stream << vector.ToString();	
				return stream;	
			}	
						
			static T Distance(const Vector2<T>& left, const Vector2<T>& right)
			{	
				return (left - right).Length();	
			}	
						
			static Vector2<T> Right()
			{	
				return Vector2<T>((T)1, (T)0);	
			}	
						
			static Vector2<T> Up()	
			{	
				return Vector2<T>((T)0, (T)1);	
			}
		};

		typedef Vector2<float> Vector2f;
		typedef Vector2<int> Vector2i;

	}
}