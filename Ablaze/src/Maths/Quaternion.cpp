#include "Quaternion.h"

namespace Ablaze
{
	namespace Maths
	{

		Quaternion::Quaternion() : Quaternion(0, 0, 0, 0)
		{
		
		}

		Quaternion::Quaternion(float x, float y, float z, float w) : Object(),
			x(x), y(y), z(z), w(w)
		{
		
		}

		Quaternion::Quaternion(const Vec4& values) : Quaternion(values.x, values.y, values.z, values.w)
		{
			
		}

		Quaternion::Quaternion(const Quaternion& other) : Quaternion(other.x, other.y, other.z, other.w)
		{
		
		}

		Mat4 Quaternion::ToMat4() const
		{
			return Mat4::FromRows(
				Vec4(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y), 0.0f),
				Vec4(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x), 0.0f),
				Vec4(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y), 0.0f),
				Vec4(0.0f, 0.0f, 0.0f, 1.0f));
		}

		Vec4 Quaternion::ToAngleAxis() const
		{
			Quaternion q(*this);
			if (q.w > 1.0f)
				q = q.Normalize();

			float w = 2.0f * (float)acos(q.w);
			float den = (float)sqrt(1.0 - q.w * q.w);
			if (den > 0.0001f)
			{
				return Vec4(Vec3(q.x, q.y, q.z) / den, w);
			}
			else
			{
				return Vec4(1, 0, 0, w);
			}
		}

		float Quaternion::GetLength() const
		{
			return sqrt(GetLengthSqrd());
		}

		float Quaternion::GetLengthSqrd() const
		{
			return Norm();
		}

		float Quaternion::Dot(const Quaternion& q) const
		{
			return (x * q.x) + (y * q.y) + (z * q.z) + (w * q.w);
		}

		Quaternion Quaternion::Conjugate() const
		{
			return Quaternion(-x, -y, -z, w);
		}

		float Quaternion::Norm() const
		{
			return x * x + y * y + z * z + w * w;
		}

		Quaternion Quaternion::Inverse() const
		{
			return Conjugate() / Norm();
		}

		Quaternion Quaternion::Normalize() const
		{
			return *this / GetLength();
		}

		float& Quaternion::operator[](int index)
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
			}
		}

		Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
		{
			return Quaternion(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w);
		}

		Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
		{
			return Quaternion(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w);
		}

		Quaternion operator-(const Quaternion& q1)
		{
			return Quaternion(-q1.x, -q1.y, -q1.z, -q1.w);
		}

		Quaternion operator*(const Quaternion& q, float s)
		{
			return Quaternion(s * q.x, s * q.y, s * q.z, s * q.w);
		}

		Quaternion operator*(float s, const Quaternion& q)
		{
			return q * s;
		}

		Vec3 operator*(const Quaternion& q, const Vec3& v)
		{
			Vec3 t_uv, t_uuv;
			Vec3 t_qvec = Vec3(q.x, q.y, q.z);
			t_uv = Vec3::Cross(t_qvec, v);
			t_uuv = Vec3::Cross(t_qvec, t_uv);
			t_uv *= 2.0f * q.w;
			t_uuv *= 2.0f;
			return v + t_uv + t_uuv;
		}

		Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
		{
			return Quaternion(
				q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x,
				-q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y,
				q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z,
				-q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w);
		}

		Quaternion operator/(const Quaternion& q, float s)
		{
			float inv = 1.0f / s;
			return q * inv;
		}

		Quaternion operator/(const Quaternion& q1, const Quaternion& q2)
		{
			return q1 * q2.Inverse();
		}

		bool operator==(const Quaternion& q1, const Quaternion& q2)
		{
			return (q1.w == q2.w && q1.x == q2.x && q1.y == q2.y && q1.z == q2.z);
		}

		bool operator!=(const Quaternion& q1, const Quaternion& q2)
		{
			return !(q1 == q2);
		}

		String Quaternion::ToString() const
		{
			return "Quaternion(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
		}

		Quaternion Quaternion::Log(const Quaternion& q)
		{
			float a = (float)acos(q.w);
			float sina = (float)sin(a);

			if (sina > 0)
				return Quaternion(a * q.x / sina, a * q.y / sina, a * q.z / sina, 0.0f);
			return Quaternion(q.x, q.y, q.z, 0.0f);
		}

		Quaternion Quaternion::Exp(const Quaternion& q)
		{
			float a = (float)sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
			float sina = (float)sin(a);
			float cosa = (float)cos(a);

			if (a > 0)
				return Quaternion(sina * q.x / a, sina * q.y / a, sina * q.z / a, cosa);
			return Quaternion(q.x, q.y, q.z, cosa);
		}

		Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, float t)
		{
			return (q1 + t * (q1 - q2)).Normalize();
		}

		Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t)
		{
			float c0, c1;
			float cos = q1.Dot(q2);
			float sign = 1;
			if (cos < 0.0f)
			{
				cos = -cos;
				sign = -1.0f;
			}

			if (cos < 1.0f - 1e-3f)
			{
				float angle = (float)acos(cos);
				float invSin = 1.0f / (float)(sqrt(1.0f - cos * cos));
				c0 = (float)sin((1.0f - t) * angle) * invSin;
				c1 = (float)sin(t * angle) * invSin;
			}
			else
			{
				c0 = 1.0f - t;
				c1 = t;
			}
			return c0 * q1 + (sign * c1) * q2;
		}

		Quaternion Quaternion::Squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& ta, const Quaternion& tb, float t)
		{
			float slerpT = 2.0f * t * (1.0f - t);
			Quaternion p = Slerp(q1, q2, t);
			Quaternion q = Slerp(ta, tb, t);
			return Slerp(p, q, slerpT);
		}

		Quaternion Quaternion::SimpleSquad(const Quaternion& prev, Quaternion q1, Quaternion q2, Quaternion post, float t)
		{
			if (prev.Dot(q1) < 0)
				q1 = -q1;
			if (q1.Dot(q2) < 0)
				q2 = -q2;
			if (q2.Dot(post) < 0)
				post = -post;

			Quaternion ta = Spline(prev, q1, q2);
			Quaternion tb = Spline(q1, q2, post);

			return Squad(q1, q2, ta, tb, t);
		}

		Quaternion Quaternion::Spline(const Quaternion& pre, const Quaternion& q, const Quaternion& post)
		{
			Quaternion cj = q.Conjugate();
			Quaternion e = q * Exp((Log(cj * pre) + Log(cj * post)) * -0.25f);
			return e;
		}

		Quaternion Quaternion::Zero()
		{
			return Quaternion(0, 0, 0, 0);
		}

		Quaternion Quaternion::Identity()
		{
			return Quaternion(0, 0, 0, 1);
		}

		Quaternion Quaternion::FromAngleAxis(float angle, const Vec3& axis)
		{
			if (axis.GetLengthSqrd() == 0.0f)
				return Identity();

			return Quaternion(Vec4(axis.Normalize() * (float)sin(angle * 0.5f), (float)cos(angle * 0.5f)));
		}

		Quaternion Quaternion::FromRotationMat(const Mat4& rotation)
		{
			int rotationLookup[] = { 1, 2, 0 };
			float t_trace = rotation.GetRow(0).x + rotation.GetRow(1).y + rotation.GetRow(2).z;
			float t_root = 0.0f;

			if (t_trace > 0.0)
			{   // |w| > 1/2
				Quaternion t_return = Zero();
				t_root = (float)sqrt(t_trace + 1.0);
				t_return.w = 0.5f * t_root;
				t_root = 0.5f / t_root;
				t_return.x = (rotation.GetRow(2).y - rotation.GetRow(1).z) * t_root;
				t_return.y = (rotation.GetRow(0).z - rotation.GetRow(2).x) * t_root;
				t_return.z = (rotation.GetRow(1).x - rotation.GetRow(0).y) * t_root;
				return t_return;
			}
			else
			{   // |w| <= 1/2
				Quaternion t_return = Zero();

				int i = 0;
				if (rotation.GetRow(1).y > rotation.GetRow(0).x) i = 1;
				if (rotation.GetRow(2).z > rotation.GetRow(i).Get(i)) i = 2;
				int j = rotationLookup[i];
				int k = rotationLookup[j];

				t_root = (float)sqrt(rotation.GetRow(i).Get(i) - rotation.GetRow(j).Get(j) - rotation.GetRow(k).Get(k) + 1.0f);
				t_return[i] = 0.5f * t_root;
				t_root = 0.5f / t_root;
				t_return.w = (rotation.GetRow(k).Get(j) - rotation.GetRow(j).Get(k)) * t_root;
				t_return[j] = (rotation.GetRow(j).Get(i) + rotation.GetRow(i).Get(j)) * t_root;
				t_return[k] = (rotation.GetRow(k).Get(i) + rotation.GetRow(i).Get(k)) * t_root;
				return t_return;
			}
		}

		std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
		{
			stream << q.ToString();
			return stream;
		}

	}
}