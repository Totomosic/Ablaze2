#pragma once
#include "Mat4.h"

namespace Ablaze
{
	namespace Maths
	{

		struct AB_API Quaternion
		{
		public:
			float x;
			float y;
			float z; 
			float w;

		public:
			Quaternion();
			Quaternion(const Vec4& values);
			Quaternion(float x, float y, float z, float w);
			Quaternion(const Quaternion& other);

			Mat4 ToMat4() const;
			Vec4 ToAngleAxis() const;
			float GetLength() const;
			float GetLengthSqrd() const;
			float Dot(const Quaternion& q) const;
			Quaternion Conjugate() const;
			float Norm() const;
			Quaternion Inverse() const;
			Quaternion Normalize() const;

			float& operator[](int index);

			friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
			friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
			friend Quaternion operator-(const Quaternion& q1);
			friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
			friend Quaternion operator*(const Quaternion& q1, float s);
			friend Quaternion operator*(float s, const Quaternion& q1);
			friend Vec3 operator*(const Quaternion& q1, const Maths::Vec3& v);
			friend Quaternion operator/(const Quaternion& q1, const Quaternion& q2);
			friend Quaternion operator/(const Quaternion& q1, float s);

			Quaternion& operator+=(const Quaternion& q2);
			Quaternion& operator-=(const Quaternion& q2);
			Quaternion& operator*=(const Quaternion& q2);
			Quaternion& operator*=(float s);
			Quaternion& operator/=(const Quaternion& q2);
			Quaternion& operator/=(float s);

			friend bool operator==(const Quaternion& q1, const Quaternion& q2);
			friend bool operator!=(const Quaternion& q1, const Quaternion& q2);

			String ToString() const;
			void Serialize(JSONwriter& writer) const;

		public:
			static Quaternion Log(const Quaternion& q);
			static Quaternion Exp(const Quaternion& q);
			static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);
			static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
			static Quaternion Squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& ta, const Quaternion& tb, float t);
			static Quaternion SimpleSquad(const Quaternion& prev, Quaternion q1, Quaternion q2, Quaternion post, float t);
			static Quaternion Spline(const Quaternion& pre, const Quaternion& q, const Quaternion& post);

			static Quaternion Zero();
			static Quaternion Identity();
			static Quaternion FromAngleAxis(float angle, const Vec3& axis);
			static Quaternion FromEuler(float pitch, float yaw, float roll);
			static Quaternion FromRotationMat(const Mat4& rotation);

			static Quaternion Deserialize(JSONnode& node);

			friend std::ostream& operator<<(std::ostream& stream, const Quaternion& q);

		};

	}
}