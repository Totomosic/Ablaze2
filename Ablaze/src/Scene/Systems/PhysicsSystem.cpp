#include "PhysicsSystem.h"

namespace Ablaze
{

	PhysicsSystem::PhysicsSystem() : System(),
		m_Gravity(9.8f), m_GravityDir(-Maths::Vector3f::Up())
	{
	
	}

	float PhysicsSystem::Gravity() const
	{
		return m_Gravity;
	}

	float& PhysicsSystem::Gravity()
	{
		return m_Gravity;
	}

	const Maths::Vector3f& PhysicsSystem::GravityDirection() const
	{
		return m_GravityDir;
	}

	Maths::Vector3f& PhysicsSystem::GravityDirection()
	{
		return m_GravityDir;
	}

	void PhysicsSystem::Execute()
	{
		std::vector<GameObject*> objects = GameObject::GetAllWith<Transform, RigidBody>();
		for (GameObject* object : objects)
		{
			Transform& transform = object->transform();
			RigidBody& rb = object->GetComponent<RigidBody>();

			if (rb.GravityEnabled())
			{
				rb.Acceleration() += m_GravityDir * m_Gravity;
			}
			
			rb.Velocity() += rb.Acceleration() * Time::DeltaTime();
			transform.Translate(rb.Velocity() * Time::DeltaTime());
			rb.Acceleration() = Maths::Vector3f(0.0f);

			rb.RotationAcceleration() += rb.RotationVelocity() * Time::DeltaTime();
			transform.Rotate(rb.RotationVelocity().x * Time::DeltaTime(), Maths::Vector3f(1, 0, 0));
			transform.Rotate(rb.RotationVelocity().y * Time::DeltaTime(), Maths::Vector3f(0, 1, 0));
			transform.Rotate(rb.RotationVelocity().z * Time::DeltaTime(), Maths::Vector3f(0, 0, 1));
			rb.RotationAcceleration() = Maths::Vector3f(0.0f);
		}
	}

}