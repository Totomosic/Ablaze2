#include "Actor.h"

namespace Ablaze
{

	Actor::Actor(const Transform& transform, const Mesh& mesh, bool addToScene) : Entity(transform, mesh, addToScene)
	{

	}

	Actor::Actor(const Transform& transform, bool addToScene) : Entity(transform, addToScene)
	{
		
	}

	Actor::Actor(const Mesh& mesh, bool addToScene) : Actor(Transform(), mesh, addToScene)
	{

	}

	Actor::Actor(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, bool addToScene) : Actor(Transform(position, rotation, scale), mesh, addToScene)
	{

	}

	Actor::Actor(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, bool addToScene) : Actor(Transform(position, rotation, scale), addToScene)
	{

	}

	Actor::Actor(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Mesh& mesh, bool addToScene) : Actor(Transform(position, rotation), mesh, addToScene)
	{

	}

	Actor::Actor(const Maths::Vec3& position, const Maths::Quaternion& rotation, bool addToScene) : Actor(Transform(position, rotation), addToScene)
	{

	}

	Actor::Actor(const Maths::Vec3& position, const Mesh& mesh, bool addToScene) : Actor(Transform(position), mesh, addToScene)
	{

	}

	Actor::Actor(const Maths::Vec3& position, bool addToScene) : Actor(Transform(position), addToScene)
	{

	}

	Actor::Actor(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, bool addToScene) : Actor(Maths::Vec3(x, y, z), rotation, scale, mesh, addToScene)
	{

	}

	Actor::Actor(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, bool addToScene) : Actor(Maths::Vec3(x, y, z), rotation, scale, addToScene)
	{

	}

	Actor::Actor(float x, float y, float z, const Maths::Quaternion& rotation, const Mesh& mesh, bool addToScene) : Actor(Maths::Vec3(x, y, z), rotation, mesh, addToScene)
	{

	}

	Actor::Actor(float x, float y, float z, const Maths::Quaternion& rotation, bool addToScene) : Actor(Maths::Vec3(x, y, z), rotation, addToScene)
	{

	}

	Actor::Actor(float x, float y, float z, const Mesh& mesh, bool addToScene) : Actor(Maths::Vec3(x, y, z), mesh, addToScene)
	{

	}

	Actor::Actor(float x, float y, float z, bool addToScene) : Actor(Maths::Vec3(x, y, z), addToScene)
	{

	}

	Actor::Actor(bool addToScene) : Actor(0, 0, 0, addToScene)
	{

	}

	const Maths::Vec3& Actor::Velocity() const
	{
		return m_Velocity;
	}

	Maths::Vec3& Actor::Velocity()
	{
		return m_Velocity;
	}

	const Maths::Vec3& Actor::Acceleration() const
	{
		return m_Acceleration;
	}

	Maths::Vec3& Actor::Acceleration()
	{
		return m_Acceleration;
	}

	const Maths::Vec3& Actor::RotationVelocity() const
	{
		return m_RotationVelocity;
	}

	Maths::Vec3& Actor::RotationVelocity()
	{
		return m_RotationVelocity;
	}

	const Maths::Vec3& Actor::RotationAcceleration() const
	{
		return m_RotationAcceleration;
	}

	Maths::Vec3& Actor::RotationAcceleration()
	{
		return m_RotationAcceleration;
	}

	void Actor::Update(double elapsedSeconds)
	{
		Entity::Update(elapsedSeconds);
		Velocity() += Acceleration() * elapsedSeconds;
		Position() += Velocity() * elapsedSeconds;
		// TODO: handle rotation;
		RotationVelocity() += RotationAcceleration() * elapsedSeconds;
	}

	String Actor::ToString() const
	{
		return "Actor";
	}

}