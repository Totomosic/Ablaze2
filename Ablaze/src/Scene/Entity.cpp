#include "Entity.h"
#include "SceneManager.h"

namespace Ablaze
{

	Entity::Entity(const Transform& transform, const Mesh& mesh, bool addToScene) : Object(),
		m_Transform(transform), m_Mesh(mesh), m_HasMesh(true)
	{
		if (SceneManager::Instance().HasScene() && addToScene)
		{
			SceneManager::Instance().CurrentScene().AddEntity(this);
		}
	}

	Entity::Entity(const Transform& transform, bool addToScene) : Object(),
		m_Transform(transform), m_HasMesh(false)
	{
		if (SceneManager::Instance().HasScene() && addToScene)
		{
			SceneManager::Instance().CurrentScene().AddEntity(this);
		}
	}

	Entity::Entity(const Mesh& mesh, bool addToScene) : Entity(Transform(), mesh, addToScene)
	{
	
	}

	Entity::Entity(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, bool addToScene) : Entity(Transform(position, rotation, scale), mesh, addToScene)
	{ 
	
	}

	Entity::Entity(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, bool addToScene) : Entity(Transform(position, rotation, scale), addToScene)
	{ 
	
	}

	Entity::Entity(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Mesh& mesh, bool addToScene) : Entity(Transform(position, rotation), mesh, addToScene)
	{
	
	}

	Entity::Entity(const Maths::Vec3& position, const Maths::Quaternion& rotation, bool addToScene) : Entity(Transform(position, rotation), addToScene)
	{ 
	
	}

	Entity::Entity(const Maths::Vec3& position, const Mesh& mesh, bool addToScene) : Entity(Transform(position), mesh, addToScene)
	{ 
	
	}

	Entity::Entity(const Maths::Vec3& position, bool addToScene) : Entity(Transform(position), addToScene)
	{ 
	
	}

	Entity::Entity(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, bool addToScene) : Entity(Maths::Vec3(x, y, z), rotation, scale, mesh, addToScene)
	{
	
	}

	Entity::Entity(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, bool addToScene) : Entity(Maths::Vec3(x, y, z), rotation, scale, addToScene)
	{
	
	}

	Entity::Entity(float x, float y, float z, const Maths::Quaternion& rotation, const Mesh& mesh, bool addToScene) : Entity(Maths::Vec3(x, y, z), rotation, mesh, addToScene)
	{
	
	}

	Entity::Entity(float x, float y, float z, const Maths::Quaternion& rotation, bool addToScene) : Entity(Maths::Vec3(x, y, z), rotation, addToScene)
	{ 
	
	}

	Entity::Entity(float x, float y, float z, const Mesh& mesh, bool addToScene) : Entity(Maths::Vec3(x, y, z), mesh, addToScene)
	{ 
	
	}

	Entity::Entity(float x, float y, float z, bool addToScene) : Entity(Maths::Vec3(x, y, z), addToScene)
	{ 
	
	}

	Entity::Entity(bool addToScene) : Entity(0, 0, 0, addToScene)
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

}