#pragma once
#include "Common.h"
#include "Scene\GameObject.h"
#include "Scene\LayerMask.h"

namespace Ablaze
{

	struct AB_API CollisionInfo
	{
	public:
		LayerMask Mask;
		std::vector<GameObject*> GameObjects;
		std::vector<Maths::Vector3f> HitLocations;
		bool DidHit;

	};

}