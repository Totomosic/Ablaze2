#pragma once
#include "AblazeInclude.h"
#include "CharacterController.h"

namespace Game
{

	class NPCController : public CharacterController
	{
	private:
		GameObject* m_Player;
		float m_Speed;
		float m_RotateSpeed;

	public:
		NPCController(GameObject* player, float speed, float rotateSpeed);

		void Update(double elapsedSeconds) override;

		String ToString() const override;
		Component* Clone() const override;

	};

}