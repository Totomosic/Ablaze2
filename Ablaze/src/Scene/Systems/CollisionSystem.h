#pragma once
#include "Systems.h"

namespace Ablaze
{

	class AB_API CollisionSystem : public System
	{
	public:
		CollisionSystem();
		void Execute() override;

	};

}