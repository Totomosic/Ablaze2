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
		Actor(const Transform& transform, const Mesh& mesh, bool addToScene = true);
		Actor(const Transform& transform, bool addToScene = true);
		Actor(const Mesh& mesh, bool addToScene = true);
		Actor(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, bool addToScene = true);
		Actor(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, bool addToScene = true);
		Actor(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Mesh& mesh, bool addToScene = true);
		Actor(const Maths::Vec3& position, const Maths::Quaternion& rotation, bool addToScene = true);
		Actor(const Maths::Vec3& position, const Mesh& mesh, bool addToScene = true);
		Actor(const Maths::Vec3& position, bool addToScene = true);
		Actor(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, bool addToScene = true);
		Actor(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, bool addToScene = true);
		Actor(float x, float y, float z, const Maths::Quaternion& rotation, const Mesh& mesh, bool addToScene = true);
		Actor(float x, float y, float z, const Maths::Quaternion& rotation, bool addToScene = true);
		Actor(float x, float y, float z, const Mesh& mesh, bool addToScene = true);
		Actor(float x, float y, float z, bool addToScene = true);
		Actor(bool addToScene = true);

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

	};

}