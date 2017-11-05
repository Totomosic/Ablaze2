#pragma once
#include "Entity.h"

namespace Ablaze
{

	class AB_API Actor : public Entity
	{
	protected:
		Maths::Vec3 m_Velocity;
		Maths::Vec3 m_Acceleration;
		Maths::Vec3 m_RotationVelocity;
		Maths::Vec3 m_RotationAcceleration;

	public:
		Actor(const Transform& transform, const Mesh& mesh);
		Actor(const Transform& transform);
		Actor(const Mesh& mesh);
		Actor();

		const Maths::Vec3& Velocity() const;
		Maths::Vec3& Velocity();
		const Maths::Vec3& Acceleration() const;
		Maths::Vec3& Acceleration();
		const Maths::Vec3& RotationVelocity() const;
		Maths::Vec3& RotationVelocity();
		const Maths::Vec3& RotationAcceleration() const;
		Maths::Vec3& RotationAcceleration();

		void Update(double elapsedSeconds) override;

		String ToString() const override;

		friend class Layer;

	};

}