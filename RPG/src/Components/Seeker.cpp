#include "Seeker.h"

namespace Game
{

	Seeker::Seeker(GameObject* target, float maxTurn) : Component(),
		m_Target(target), m_MaxTurn(maxTurn)
	{
		
	}

	void Seeker::Update(double elapsedSeconds)
	{
		Vector3f direction = (m_Target->transform().Position() - m_GameObject->transform().Position());
		RigidBody& rb = m_GameObject->GetComponent<RigidBody>();
		rb.Acceleration() = direction.Normalize() * min(m_MaxTurn, direction.Length());
	}

	String Seeker::ToString() const
	{
		return "Seeker";
	}

	Component* Seeker::Clone() const
	{
		return new Seeker(m_Target, m_MaxTurn);
	}

}