#pragma once
#include "AblazeInclude.h"

namespace Presidents
{

	class AI : public Component
	{
	private:


	public:
		AI();

		void Update(double elapsedSeconds) override;

		String ToString() const override;
		Component* Clone() const override;

	};

}