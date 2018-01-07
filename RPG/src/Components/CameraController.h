#pragma once
#include "AblazeInclude.h"

namespace Game
{

	class CameraController : public Component
	{
	private:
		float m_Speed;

	public:
		CameraController(float speed = 0.3f);

		void Update(double elapsedSeconds) override;

		String ToString() const override;
		Component* Clone() const override;

	};

}