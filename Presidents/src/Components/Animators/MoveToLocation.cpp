#include "MoveToLocation.h"

namespace Presidents
{

	MoveToLocation::MoveToLocation(const Vector3f& location, float time) : Component(),
		m_Target(location), m_Time(time), m_Velocity(0.0f)
	{
	
	}

	void MoveToLocation::Update(double elapsedSeconds)
	{
		if (Vector3f::Distance(m_Target, m_GameObject->transform().LocalPosition()) > 0.01f)
		{
			m_GameObject->transform().LocalPosition() = Vector3f::SmoothDamp(m_GameObject->transform().LocalPosition(), m_Target, &m_Velocity, m_Time, elapsedSeconds);
		}
		else
		{
			m_GameObject->Components().RemoveComponent(this);
		}
	}

	String MoveToLocation::ToString() const
	{
		return "MoveToLocation";
	}

	Component* MoveToLocation::Clone() const
	{
		MoveToLocation* mtl = new MoveToLocation(m_Target, m_Time);
		return mtl;
	}

}