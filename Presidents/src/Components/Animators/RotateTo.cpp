#include "RotateTo.h"

namespace Presidents
{

	RotateTo::RotateTo(const Quaternion& target, float time) : Component(),
		m_Target(target), m_Time(time), m_CurrentTime(0.0f), m_Current(0.0f), m_Velocity(0.0f)
	{
	
	}

	void RotateTo::Update(double elapsedSeconds)
	{
		if (m_GameObject->transform().LocalRotation() == m_Target)
		{
			m_GameObject->Components().RemoveComponent(this);
			return;
		}
		Vector3f now = Vector3f::SmoothDamp(m_Current, Vector3f(1, 0, 0), &m_Velocity, m_Time, elapsedSeconds);
		float dist = now.x;
		m_GameObject->transform().LocalRotation() = Quaternion::Slerp(m_GameObject->transform().LocalRotation(), m_Target, dist);
	}

	String RotateTo::ToString() const
	{
		return "RotateTo";
	}

	Component* RotateTo::Clone() const
	{
		return new RotateTo(m_Target, m_Time);
	}

}