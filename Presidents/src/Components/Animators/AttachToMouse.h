#pragma once
#include "AblazeInclude.h"

namespace Presidents
{

	class AttachToMouse : public Component
	{
	public:
		void Update(double elapsedSeconds) override;

		String ToString() const override;
		Component* Clone() const override;

	};

}