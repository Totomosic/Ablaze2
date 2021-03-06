#include "RigidBody.h"

namespace Ablaze
{

	RigidBody::RigidBody(float mass, bool gravityEnabled) : Component(),
		m_Mass(mass), m_Velocity(0.0f), m_Acceleration(0.0f), m_RotationVelocity(0.0f), m_RotationAcceleration(0.0f), m_GravityEnabled(gravityEnabled)
	{
	
	}

	RigidBody::RigidBody(bool gravityEnabled, float mass) : RigidBody(mass, gravityEnabled)
	{
	
	}

	RigidBody::RigidBody() : RigidBody(1.0f)
	{
	
	}

	float RigidBody::Mass() const
	{
		return m_Mass;
	}

	float& RigidBody::Mass()
	{
		return m_Mass;
	}

	const Maths::Vector3f& RigidBody::Velocity() const
	{
		return m_Velocity;
	}

	Maths::Vector3f& RigidBody::Velocity()
	{
		return m_Velocity;
	}

	const Maths::Vector3f& RigidBody::Acceleration() const
	{
		return m_Acceleration;
	}

	Maths::Vector3f& RigidBody::Acceleration()
	{
		return m_Acceleration;
	}

	const Maths::Vector3f& RigidBody::RotationVelocity() const
	{
		return m_RotationVelocity;
	}

	Maths::Vector3f& RigidBody::RotationVelocity()
	{
		return m_RotationVelocity;
	}

	const Maths::Vector3f& RigidBody::RotationAcceleration() const
	{
		return m_RotationAcceleration;
	}

	Maths::Vector3f& RigidBody::RotationAcceleration()
	{
		return m_RotationAcceleration;
	}

	bool RigidBody::GravityEnabled() const
	{
		return m_GravityEnabled;
	}

	bool& RigidBody::GravityEnabled()
	{
		return m_GravityEnabled;
	}

	void RigidBody::ApplyForce(const Maths::Vector3f& force)
	{
		// F = ma
		m_Acceleration += force / Mass();
	}

	void RigidBody::ApplyForce(float magnitude, const Maths::Vector3f& direction)
	{
		ApplyForce(direction * magnitude);
	}

	String RigidBody::ToString() const
	{
		return "RigidBody";
	}

	void RigidBody::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("Mass", m_Mass);
		writer.WriteObject("Velocity", m_Velocity);
		writer.WriteObject("Acceleration", m_Acceleration);
		writer.WriteObject("RotationVelocity", m_RotationVelocity);
		writer.WriteObject("RotationAcceleration", m_RotationAcceleration);
		writer.WriteAttribute("GravityEnabled", m_GravityEnabled);
		writer.EndObject();
	}

	Component* RigidBody::Clone() const
	{
		RigidBody* rb = new RigidBody(m_Mass, m_GravityEnabled);
		rb->Velocity() = Velocity();
		rb->Acceleration() = Acceleration();
		rb->RotationVelocity() = RotationVelocity();
		rb->RotationAcceleration() = RotationAcceleration();
		return rb;
	}

}