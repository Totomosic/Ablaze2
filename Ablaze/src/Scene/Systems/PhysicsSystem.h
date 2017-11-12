#pragma once
#include "Systems.h"

namespace Ablaze
{

	class AB_API PhysicsSystem : public System
	{
	private:
		float m_Gravity;
		Maths::Vec3 m_GravityDir;

	public:
		PhysicsSystem();

		float Gravity() const;
		float& Gravity();
		const Maths::Vec3& GravityDirection() const;
		Maths::Vec3& GravityDirection();

		void Execute() override;

	};

}