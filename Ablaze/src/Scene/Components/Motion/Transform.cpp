#include "Transform.h"

namespace Ablaze
{

	Transform::Transform::Transform(const Maths::Vector3f& position, const Maths::Quaternion& rotation, const Maths::Vector3f& scale) : Component(),
		m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{

	}

	Transform::Transform() : Transform(Maths::Vector3f(0, 0, 0))
	{

	}

	Transform::Transform(const Maths::Vector3f& position) : Transform(position, Maths::Quaternion::Identity())
	{

	}

	Transform::Transform(const Maths::Vector3f& position, const Maths::Quaternion& rotation) : Transform(position, rotation, Maths::Vector3f(1, 1, 1))
	{

	}

	Transform::Transform(const Maths::Vector3f& position, const Maths::Vector3f& scale) : Transform(position, Maths::Quaternion::Identity(), scale)
	{

	}

	Transform::Transform(const Maths::Quaternion& rotation, const Maths::Vector3f& scale) : Transform(Maths::Vector3f(0, 0, 0), rotation, scale)
	{

	}

	const Maths::Vector3f Transform::Position() const
	{
		if (m_GameObject == nullptr || !m_GameObject->HasParent() || !m_GameObject->Parent()->HasComponent<Transform>())
		{
			return m_Position;
		}
		return ToMatrix().Column(3).xyz();
	}

	const Maths::Quaternion Transform::Rotation() const
	{
		if (m_GameObject == nullptr || !m_GameObject->HasParent() || !m_GameObject->Parent()->HasComponent<Transform>())
		{
			return m_Rotation;
		}
		return m_GameObject->Parent()->GetComponent<Transform>().Rotation() * m_Rotation;
	}

	const Maths::Vector3f Transform::Scale() const
	{
		if (m_GameObject == nullptr || !m_GameObject->HasParent() || !m_GameObject->Parent()->HasComponent<Transform>())
		{
			return m_Scale;
		}
		return m_GameObject->Parent()->GetComponent<Transform>().Scale() * m_Scale;
	}

	const Maths::Vector3f& Transform::LocalPosition() const
	{
		return m_Position;
	}

	Maths::Vector3f& Transform::LocalPosition()
	{
		return m_Position;
	}

	const Maths::Quaternion& Transform::LocalRotation() const
	{
		return m_Rotation;
	}

	Maths::Quaternion& Transform::LocalRotation()
	{
		return m_Rotation;
	}

	const Maths::Vector3f& Transform::LocalScale() const
	{
		return m_Scale;
	}

	Maths::Vector3f& Transform::LocalScale()
	{
		return m_Scale;
	}

	Maths::Vector3f Transform::Forward() const
	{
		return Rotation() * Maths::Vector3f(0, 0, -1);
	}

	Maths::Vector3f Transform::Right() const
	{
		return Rotation() * Maths::Vector3f(1, 0, 0);
	}

	Maths::Vector3f Transform::Up() const
	{
		return Rotation() * Maths::Vector3f(0, 1, 0);
	}

	void Transform::SetLocalPosition(const Maths::Vector3f& position)
	{
		m_Position = position;
	}

	void Transform::SetLocalPosition(float x, float y, float z)
	{
		SetLocalPosition(Maths::Vector3f(x, y, z));
	}

	void Transform::Translate(const Maths::Vector3f& translation)
	{
		m_Position += translation;
	}

	void Transform::Translate(float x, float y, float z)
	{
		Translate(Maths::Vector3f(x, y, z));
	}

	void Transform::SetLocalScale(const Maths::Vector3f& scale)
	{
		m_Scale = scale;
	}

	void Transform::SetLocalScale(float scale)
	{
		SetLocalScale(Maths::Vector3f(scale));
	}

	void Transform::SetLocalScale(float x, float y, float z)
	{
		SetLocalScale(Maths::Vector3f(x, y, z));
	}

	void Transform::Rotate(float angle, const Maths::Vector3f& axis, Space space, Angle angleType)
	{
		Maths::Vector3f a = axis;
		if (space == Space::World)
		{
			a = m_Rotation.Inverse() * a;
		}
		if (angleType == Angle::Degrees)
		{
			angle = ToRadians(angle);
		}
		Maths::Quaternion rotation = Maths::Quaternion::FromAngleAxis(angle, a);
		m_Rotation *= rotation;
	}

	void Transform::Rotate(const Maths::Quaternion& quaternion)
	{
		m_Rotation *= quaternion;
	}

	void Transform::Reset()
	{
		m_Rotation = Maths::Quaternion::Identity();
		m_Position = Maths::Vector3f(0, 0, 0);
		m_Scale = Maths::Vector3f(1, 1, 1);
	}

	Maths::Matrix4f Transform::ToMatrix() const
	{
		if (m_GameObject == nullptr || !m_GameObject->HasParent() || !m_GameObject->Parent()->HasComponent<Transform>())
		{
			return Maths::Matrix4f::Translation(m_Position) * m_Rotation.ToMatrix4f() * Maths::Matrix4f::Scale(m_Scale);
		}
		return m_GameObject->Parent()->GetComponent<Transform>().ToMatrix() * Maths::Matrix4f::Translation(m_Position) * m_Rotation.ToMatrix4f() * Maths::Matrix4f::Scale(m_Scale);
	}

	String Transform::ToString() const
	{
		return "Transform";
	}

	Component* Transform::Clone() const
	{
		Transform* t = new Transform(m_Position, m_Rotation, m_Scale);
		return t;
	}

	void Transform::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteObject("Position", LocalPosition());
		writer.WriteObject("Rotation", LocalRotation());
		writer.WriteObject("Scale", LocalScale());
		writer.EndObject();
	}

	Transform Transform::operator+(const Transform& other) const
	{
		Transform t = *this;
		// Combine rotation quaternions
		t.Translate(other.m_Position);
		return t;
	}

}