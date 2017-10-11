#include "Transform.h"

namespace Ablaze
{

	Transform::Transform::Transform(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale) : Object(),
		m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
	
	}

	Transform::Transform() : Transform(Maths::Vec3(0, 0, 0))
	{ 
	
	}

	Transform::Transform(const Maths::Vec3& position) : Transform(position, Maths::Quaternion::Identity())
	{ 
	
	}

	Transform::Transform(const Maths::Vec3& position, const Maths::Quaternion& rotation) : Transform(position, rotation, Maths::Vec3(1, 1, 1))
	{ 
	
	}

	Transform::Transform(const Maths::Vec3& position, const Maths::Vec3& scale) : Transform(position, Maths::Quaternion::Identity(), scale)
	{
	
	}

	Transform::Transform(const Maths::Quaternion& rotation, const Maths::Vec3& scale) : Transform(Maths::Vec3(0, 0, 0), rotation, scale)
	{

	}

	const Maths::Vec3& Transform::Position() const
	{
		return m_Position;
	}

	Maths::Vec3& Transform::Position()
	{
		return m_Position;
	}

	const Maths::Quaternion& Transform::Rotation() const
	{
		return m_Rotation;
	}

	Maths::Quaternion& Transform::Rotation()
	{
		return m_Rotation;
	}

	const Maths::Vec3& Transform::Scale() const
	{
		return m_Scale;
	}

	Maths::Vec3& Transform::Scale()
	{
		return m_Scale;
	}

	Maths::Vec3 Transform::Forward() const
	{
		return Maths::Vec3(0, 0, -1); // TODO: fix
	}

	Maths::Vec3 Transform::Right() const
	{
		return Maths::Vec3(1, 0, 0); // TODO: fix
	}

	Maths::Vec3 Transform::Up() const
	{
		return Maths::Vec3(0, 1, 0); // TODO: fix
	}

	void Transform::Translate(const Maths::Vec3& translation)
	{
		m_Position += translation;
	}

	void Transform::Rotate(float angle, const Maths::Vec3& axis, Space space, Angle angleType)
	{
		// TODO: implement
	}

	Maths::Mat4 Transform::ToMatrix() const
	{
		return Maths::Mat4::Translation(m_Position) * m_Rotation.ToMat4() * Maths::Mat4::Scale(m_Scale);
	}

	String Transform::ToString() const
	{
		return "Transform";
	}

	Transform Transform::operator+(const Transform& other) const
	{
		Transform t = *this;
		// Combine rotation quaternions
		t.Translate(other.m_Position);
		return t;
	}

}