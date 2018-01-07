#include "CameraController.h"

namespace Game
{

	CameraController::CameraController(float speed) : Component(),
		m_Speed(speed)
	{
	
	}

	void CameraController::Update(double elapsedSeconds)
	{
		Transform& t = m_GameObject->transform();
		if (Input::MouseButtonDown(MouseButton::Middle))
		{
			t.Rotate(Input::RelMousePosition().x * m_Speed * Time::DeltaTime(), Vector3f::Up(), Space::World);
			t.Rotate(-Input::RelMousePosition().y * m_Speed * Time::DeltaTime(), Vector3f::Right(), Space::Local);
		}
	}

	String CameraController::ToString() const
	{
		return "CameraController";
	}

	Component* CameraController::Clone() const
	{
		return new CameraController(m_Speed);
	}

}