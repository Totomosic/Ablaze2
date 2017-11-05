#include "Entity.h"
#include "SceneManager.h"

namespace Ablaze
{

	Entity::Entity(const Transform& transform, const Mesh& mesh) : Object(),
		m_Transform(transform), m_Mesh(mesh), m_HasMesh(true), m_Layer(nullptr), m_IsTagged(false)
	{
		
	}

	Entity::Entity(const Transform& transform) : Object(),
		m_Transform(transform), m_HasMesh(false), m_Layer(nullptr), m_IsTagged(false)
	{

	}

	Entity::Entity(const Mesh& mesh) : Entity(Transform(), mesh)
	{
	
	}

	Entity::Entity() : Entity(Transform())
	{

	}

	const Transform& Entity::GetTransform() const
	{
		return m_Transform;
	}

	Transform& Entity::GetTransform()
	{
		return m_Transform;
	}

	const Mesh& Entity::GetMesh() const
	{
		return m_Mesh;
	}

	Mesh& Entity::GetMesh()
	{
		return m_Mesh;
	}

	bool Entity::HasMesh() const
	{
		return m_HasMesh;
	}

	const Maths::Vec3& Entity::Position() const
	{
		return GetTransform().Position();
	}

	Maths::Vec3& Entity::Position()
	{
		return GetTransform().Position();
	}

	const Maths::Quaternion& Entity::Rotation() const
	{
		return GetTransform().Rotation();
	}

	Maths::Quaternion& Entity::Rotation()
	{
		return GetTransform().Rotation();
	}

	const Maths::Vec3& Entity::Scale() const
	{
		return GetTransform().Scale();
	}

	Maths::Vec3& Entity::Scale()
	{
		return GetTransform().Scale();
	}

	Maths::Vec3 Entity::Forward() const
	{
		return m_Transform.Forward();
	}

	Maths::Vec3 Entity::Right() const
	{
		return m_Transform.Right();
	}

	Maths::Vec3 Entity::Up() const
	{
		return m_Transform.Up();
	}

	void Entity::SetTransform(const Transform& transform)
	{
		m_Transform = transform;
	}

	void Entity::SetMesh(const Mesh& mesh)
	{
		m_Mesh = mesh;
		m_HasMesh = true;
	}

	void Entity::DeleteMesh()
	{
		m_HasMesh = false;
	}

	void Entity::SetName(const String& name)
	{
		if (!m_IsTagged && m_Layer != nullptr)
		{
			m_Layer->TagEntity(this, name);
			m_IsTagged = true;
		}
	}

	void Entity::Rotate(float angle, const Maths::Vec3& axis, Space space, Angle angleType)
	{
		m_Transform.Rotate(angle, axis, space, angleType);
	}

	void Entity::Update(double elapsedSeconds)
	{
	
	}

	void Entity::Tick()
	{
	
	}

	String Entity::ToString() const
	{
		return "Entity";
	}

	void Entity::SetLayer(Layer* layer)
	{
		m_Layer = layer;
	}

}