#pragma once
#include "AblazeInclude.h"

namespace Presidents
{

	class MoveToLocation : public Component
	{
	private:
		Vector3f m_Target;
		float m_Time;
		Vector3f m_Velocity;

	public:
		MoveToLocation(const Vector3f& location, float time);

		void Update(double elapsedSeconds) override;

		String ToString() const override;
		Component* Clone() const override;

	};

}