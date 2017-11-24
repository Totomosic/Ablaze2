#include "Transform.h"

namespace Ablaze
{

	Transform::Transform::Transform(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale) : Component(),
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

	const Maths::Vec3 Transform::Position() const
	{
		if (m_GameObject == nullptr || !m_GameObject->HasParent() || !m_GameObject->Parent()->HasComponent<Transform>())
		{
			return m_Position;
		}
		return ToMatrix().GetColumn(3).xyz();
	}

	const Maths::Quaternion Transform::Rotation() const
	{
		if (m_GameObject == nullptr || !m_GameObject->HasParent() || !m_GameObject->Parent()->HasComponent<Transform>())
		{
			return m_Rotation;
		}
		return m_GameObject->Parent()->GetComponent<Transform>().Rotation() * m_Rotation;
	}

	const Maths::Vec3 Transform::Scale() const
	{
		if (m_GameObject == nullptr || !m_GameObject->HasParent() || !m_GameObject->Parent()->HasComponent<Transform>())
		{
			return m_Scale;
		}
		return m_GameObject->Parent()->GetComponent<Transform>().Scale() * m_Scale;
	}

	const Maths::Vec3& Transform::LocalPosition() const
	{
		return m_Position;
	}

	Maths::Vec3& Transform::LocalPosition()
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

	const Maths::Vec3& Transform::LocalScale() const
	{
		return m_Scale;
	}

	Maths::Vec3& Transform::LocalScale()
	{
		return m_Scale;
	}

	Maths::Vec3 Transform::Forward() const
	{
		return Rotation() * Maths::Vec3(0, 0, -1);
	}

	Maths::Vec3 Transform::Right() const
	{
		return Rotation() * Maths::Vec3(1, 0, 0);
	}

	Maths::Vec3 Transform::Up() const
	{
		return Rotation() * Maths::Vec3(0, 1, 0);
	}

	void Transform::Translate(const Maths::Vec3& translation)
	{
		m_Position += translation;
	}

	void Transform::SetScale(const Maths::Vec3& scale)
	{
		m_Scale = scale;
	}

	void Transform::SetScale(float scale)
	{
		SetScale(Maths::Vec3(scale));
	}

	void Transform::Rotate(float angle, const Maths::Vec3& axis, Space space, Angle angleType)
	{
		Maths::Vec3 a = axis;
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

	Maths::Mat4 Transform::ToMatrix() const
	{
		if (m_GameObject == nullptr || !m_GameObject->HasParent() || !m_GameObject->Parent()->HasComponent<Transform>())
		{
			return Maths::Mat4::Translation(m_Position) * m_Rotation.ToMat4() * Maths::Mat4::Scale(m_Scale);
		}
		return m_GameObject->Parent()->GetComponent<Transform>().ToMatrix() * Maths::Mat4::Translation(m_Position) * m_Rotation.ToMat4() * Maths::Mat4::Scale(m_Scale);
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

	Component* Transform::Deserialize(JSONnode& node) const
	{
		Transform* t = new Transform;
		t->LocalPosition() = Maths::Vec3::Deserialize(node["Position"]);
		t->LocalRotation() = Maths::Quaternion::Deserialize(node["Rotation"]);
		t->LocalScale() = Maths::Vec3::Deserialize(node["Scale"]);
		return t;
	}

	Transform Transform::operator+(const Transform& other) const
	{
		Transform t = *this;
		// Combine rotation quaternions
		t.Translate(other.m_Position);
		return t;
	}

}