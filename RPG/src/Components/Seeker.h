#pragma once
#include "AblazeInclude.h"

namespace Game
{

	class Seeker : public Component
	{
	private:
		GameObject* m_Target;
		float m_MaxTurn;

	public:
		Seeker(GameObject* target, float maxTurn);

		void Update(double elapsedSeconds) override;

		String ToString() const override;
		Component* Clone() const override;

	};

}