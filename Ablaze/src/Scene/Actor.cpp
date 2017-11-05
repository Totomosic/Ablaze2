#include "Actor.h"

namespace Ablaze
{

	Actor::Actor(const Transform& transform, const Mesh& mesh) : Entity(transform, mesh)
	{

	}

	Actor::Actor(const Transform& transform) : Entity(transform)
	{
		
	}

	Actor::Actor(const Mesh& mesh) : Actor(Transform(), mesh)
	{

	}

	Actor::Actor() : Actor(Transform())
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