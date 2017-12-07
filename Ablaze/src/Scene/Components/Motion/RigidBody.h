#pragma once
#include "Scene\Components\Component.h"
#include "Common.h"

namespace Ablaze
{

	class AB_API RigidBody : public Component
	{
	private:
		float m_Mass;
		Maths::Vector3f m_Velocity;
		Maths::Vector3f m_Acceleration;
		Maths::Vector3f m_RotationVelocity;
		Maths::Vector3f m_RotationAcceleration;
		bool m_GravityEnabled;

	public:
		RigidBody(float mass, bool gravityEnabled = true);
		RigidBody(bool gravityEnabled, float mass = 1.0f);
		RigidBody();

		float Mass() const;
		float& Mass();
		const Maths::Vector3f& Velocity() const;
		Maths::Vector3f& Velocity();
		const Maths::Vector3f& Acceleration() const;
		Maths::Vector3f& Acceleration();
		const Maths::Vector3f& RotationVelocity() const;
		Maths::Vector3f& RotationVelocity();
		const Maths::Vector3f& RotationAcceleration() const;
		Maths::Vector3f& RotationAcceleration();
		bool GravityEnabled() const;
		bool& GravityEnabled();

		void ApplyForce(const Maths::Vector3f& force);
		void ApplyForce(float magnitude, const Maths::Vector3f& direction);

		String ToString() const override;
		Component* Clone() const override;
		void Serialize(JSONwriter& writer) const override;

	};

}