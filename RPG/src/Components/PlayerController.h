#pragma once
#include "AblazeInclude.h"
#include "CharacterController.h"

namespace Game
{

	class PlayerController : public CharacterController
	{
	private:
		float m_Speed;
		float m_RotateSpeed;

	public:
		PlayerController(float speed, float rotateSpeed);

		void Update(double elapsedSeconds) override;

		String ToString() const override;
		Component* Clone() const override;

	};

}