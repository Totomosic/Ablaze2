#include "Wave.h"

namespace CubeWave
{

	Wave::Wave(GameObject* center, float speed, float offset, float min, float max, float maxDist) : Component(),
		m_Center(center), m_Angle(0.0f), m_Speed(speed), m_Offset(offset), m_Min(min), m_Max(max), m_MaxDist(maxDist)
	{
	
	}

	void Wave::Start()
	{
		
	}

	void Wave::Update(double elapsedSeconds)
	{
		Matrix4f& transform = m_GameObject->mesh().GetTransform(0);
		float distance = Vector2f::Distance(m_GameObject->transform().Position().xz(), m_Center->transform().Position().xz());
		float offset = Map(distance, 0, m_MaxDist, 0, m_Offset);
		float yScale = Map(sin(m_Angle + offset), -1.0f, 1.0f, m_Min, m_Max);
		transform = Matrix4f::Scale(1, yScale, 1);
		m_Angle += m_Speed * Time::DeltaTime();
	}

	Component* Wave::Clone() const
	{
		Wave* wave = new Wave(m_Center, m_Speed, m_Offset, m_Min, m_Max, m_MaxDist);
		wave->m_Angle = m_Angle;
		return wave;
	}

	String Wave::ToString() const
	{
		return "Wave";
	}

}