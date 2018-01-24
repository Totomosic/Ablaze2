#include "Follow.h"

namespace Game
{

	Follow::Follow(GameObject* target, float speed) : Component(),
		m_Target(target), m_Speed(speed), m_Velocity(0.0f)
	{
	
	}

	void Follow::LateUpdate(double elapsedSeconds)
	{
		Transform& t = m_GameObject->transform();
		Vector3f target = m_Target->transform().Position();
		target.y = t.Position().y;
		t.LocalPosition() = Vector3f::SmoothDamp(t.LocalPosition(), target, &m_Velocity, 0.5f, Time::DeltaTime());
	}

	String Follow::ToString() const
	{
		return "Follow";
	}

	Component* Follow::Clone() const
	{
		return new Follow(m_Target, m_Speed);
	}

}