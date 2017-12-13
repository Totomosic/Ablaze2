#include "Pathing.h"

Pathing::Pathing(const Vector3f& target, float speed) : Component(),
	m_Target(target), m_Speed(speed)
{

}

Pathing::Pathing(float speed) : Component(),
	m_Speed(speed)
{
	Disable();
}

bool Pathing::HasReachedTarget() const
{
	return Vector3f::Distance(m_GameObject->transform().Position(), m_Target) < 0.01f;
}

void Pathing::Update(double elapsedSeconds)
{
	if (HasReachedTarget())
	{
		return;
	}
	Vector3f direction = (m_Target - m_GameObject->transform().Position()).Normalize();
	m_GameObject->transform().LocalPosition() += direction * m_Speed * elapsedSeconds;
}

void Pathing::SetTarget(const Maths::Vector3f& target)
{
	m_Target = target;
	Enable();
}

void Pathing::SetSpeed(float speed)
{
	m_Speed = speed;
}

Component* Pathing::Clone() const
{
	Pathing* p = new Pathing(m_Target, m_Speed);
	return p;
}

String Pathing::ToString() const
{
	return "Pathing";
}