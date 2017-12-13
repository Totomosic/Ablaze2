#pragma once
#include "Common.h"
#include "Scene\GameObject.h"
#include "Scene\LayerMask.h"

namespace Ablaze
{

	struct AB_API RaycastHit
	{
	public:
		Maths::Ray Ray;
		std::vector<GameObject*> GameObjects;
		LayerMask Mask;
		std::vector<Maths::Vector3f> HitLocations;
		bool DidHit;

	};

}