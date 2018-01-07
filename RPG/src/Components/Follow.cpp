#include "Follow.h"

namespace Game
{

	Follow::Follow(GameObject* target, float speed) : Component(),
		m_Target(target), m_Speed(speed)
	{
	
	}

	void Follow::LateUpdate(double elapsedSeconds)
	{
		Transform& t = m_GameObject->transform();
		t.LocalPosition() = Vector3f(m_Target->transform().Position().x, t.LocalPosition().y, m_Target->transform().Position().z);
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