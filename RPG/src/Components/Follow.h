#pragma once
#include "AblazeInclude.h"

namespace Game
{

	class Follow : public Component
	{
	private:
		GameObject* m_Target;
		float m_Speed;

	public:
		Follow(GameObject* target, float speed);

		void LateUpdate(double elapsedSeconds) override;

		String ToString() const override;
		Component* Clone() const override;

	};

}