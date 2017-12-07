#pragma once
#include "Systems.h"

namespace Ablaze
{

	class AB_API PhysicsSystem : public System
	{
	private:
		float m_Gravity;
		Maths::Vector3f m_GravityDir;

	public:
		PhysicsSystem();

		float Gravity() const;
		float& Gravity();
		const Maths::Vector3f& GravityDirection() const;
		Maths::Vector3f& GravityDirection();

		void Execute() override;

	};

}