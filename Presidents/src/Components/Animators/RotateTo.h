#pragma once
#include "AblazeInclude.h"

namespace Presidents
{

	class RotateTo : public Component
	{
	private:
		Quaternion m_Target;
		float m_Time;
		float m_CurrentTime;

		Vector3f m_Current;
		Vector3f m_Velocity;

	public:
		RotateTo(const Quaternion& target, float time);

		void Update(double elapsedSeconds) override;
		
		String ToString() const override;
		Component* Clone() const override;

	};

}