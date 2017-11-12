#pragma once
#include "Common.h"

namespace Ablaze
{

	class BoxCollider;

	struct AB_API Endpoint
	{
		BoxCollider* Owner;
		float Value;
		bool IsMin;
	};

}