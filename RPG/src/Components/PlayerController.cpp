#include "PlayerController.h"
#include "Seeker.h"

namespace Game
{

	PlayerController::PlayerController(float speed, float rotateSpeed) : CharacterController(),
		m_Speed(speed), m_RotateSpeed(rotateSpeed)
	{
	
	}

	void PlayerController::Update(double elapsedSeconds)
	{
		Transform& t = m_GameObject->transform();
		if (Input::KeyDown(Keycode::A))
		{
			t.LocalPosition() += -Vector3f::Right() * m_Speed * Time::DeltaTime();
		}
		if (Input::KeyDown(Keycode::D))
		{
			t.LocalPosition() += Vector3f::Right() * m_Speed * Time::DeltaTime();
		}
		if (Input::KeyDown(Keycode::W))
		{
			t.LocalPosition() += Vector3f::Forward() * m_Speed * Time::DeltaTime();
		}
		if (Input::KeyDown(Keycode::S))
		{
			t.LocalPosition() += -Vector3f::Forward() * m_Speed * Time::DeltaTime();
		}

		if (Input::MouseButtonPressed(MouseButton::Left))
		{
			Fire(m_Speed * 5, m_GameObject->transform().Forward());
		}

		if (Input::MouseButtonPressed(MouseButton::Right))
		{
			ShotgunFire(m_Speed * 2, 10, m_GameObject->transform().Forward(), PI / 45.0f);
		}

		if (Input::KeyPressed(Keycode::R))
		{
			Vector3f mousePosition = Input::MousePosition();
			GameObject& camera = m_GameObject->GetLayer()->GetActiveCamera();
			mousePosition.z = camera.transform().LocalPosition().z;
			Vector3f worldPoint = camera.GetComponent<Camera>().ScreenToWorldPoint(mousePosition);
			Rockets(m_Speed * 3, 10, worldPoint);
		}

		if (Input::KeyPressed(Keycode::SPACE))
		{
			GameObject* sphere = Fire(m_Speed * 0.5f, m_GameObject->transform().Forward(), ResourceManager::Sphere(), 0.0f, 1.5f, ResourceManager::LightingColorShader(), Color(50));
		}
	}

	String PlayerController::ToString() const
	{
		return "PlayerController";
	}

	Component* PlayerController::Clone() const
	{
		return new PlayerController(m_Speed, m_RotateSpeed);
	}

}