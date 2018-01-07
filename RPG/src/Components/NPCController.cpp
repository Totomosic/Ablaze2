#include "NPCController.h"
#include "Seeker.h"

namespace Game
{

	NPCController::NPCController(GameObject* player, float speed, float rotateSpeed) : CharacterController(),
		m_Player(player), m_Speed(speed), m_RotateSpeed(rotateSpeed)
	{

	}

	void NPCController::Update(double elapsedSeconds)
	{
		Transform& t = m_GameObject->transform();
		t.LocalRotation() = Quaternion::LookAt(m_Player->transform().Position() - m_GameObject->transform().Position());

		if (Random::NextFloat(0, 100) < 2)
		{
			Fire(m_Speed * 5, m_GameObject->transform().Forward());
		}

		if (Random::NextFloat(0, 100) < 0.5f)
		{
			ShotgunFire(m_Speed * 2, 10, m_GameObject->transform().Forward(), PI / 45.0f);
		}

		if (Random::NextFloat(0, 100) < 0.1f)
		{
			GameObject* sphere = Fire(m_Speed * 0.5f, m_GameObject->transform().Forward(), ResourceManager::Sphere(), 0.0f, 1.5f, ResourceManager::LightingColorShader(), Color(50));
		}
	}

	String NPCController::ToString() const
	{
		return "NPCController";
	}

	Component* NPCController::Clone() const
	{
		return new NPCController(m_Player, m_Speed, m_RotateSpeed);
	}

}