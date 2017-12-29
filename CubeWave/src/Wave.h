#pragma once
#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::Maths;

namespace CubeWave
{

	class Wave : public Component
	{
	private:
		GameObject* m_Center;
		float m_Angle;
		float m_Speed;
		float m_Offset;
		float m_Min;
		float m_Max;
		float m_MaxDist;

	public:
		Wave(GameObject* center, float speed, float offset, float min, float max, float maxDist);

		void Update(double elapsedSeconds) override;

		Component* Clone() const override;
		String ToString() const override;

	};

}