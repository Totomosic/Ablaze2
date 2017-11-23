#pragma once
#include "Scene\Components\Component.h"
#include "Common.h"

namespace Ablaze
{

	class AB_API RigidBody : public Component
	{
	private:
		float m_Mass;
		Maths::Vec3 m_Velocity;
		Maths::Vec3 m_Acceleration;
		Maths::Vec3 m_RotationVelocity;
		Maths::Vec3 m_RotationAcceleration;
		bool m_GravityEnabled;

	public:
		RigidBody(float mass, bool gravityEnabled = true);
		RigidBody(bool gravityEnabled, float mass = 1.0f);
		RigidBody();

		float Mass() const;
		float& Mass();
		const Maths::Vec3& Velocity() const;
		Maths::Vec3& Velocity();
		const Maths::Vec3& Acceleration() const;
		Maths::Vec3& Acceleration();
		const Maths::Vec3& RotationVelocity() const;
		Maths::Vec3& RotationVelocity();
		const Maths::Vec3& RotationAcceleration() const;
		Maths::Vec3& RotationAcceleration();
		bool GravityEnabled() const;
		bool& GravityEnabled();

		void ApplyForce(const Maths::Vec3& force);
		void ApplyForce(float magnitude, const Maths::Vec3& direction);

		String ToString() const override;
		Component* Clone() const override;
		void Serialize(JSONwriter& writer) const override;

	};

}