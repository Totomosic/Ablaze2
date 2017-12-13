#pragma once
#include "structs\__structs__.h"
#include "PhysicsMaterial.h"

namespace Ablaze
{

	class GameObject;

	class AB_API Physics
	{
	private:
		struct AB_API RaycastPlaceholder
		{
			GameObject* Obj;
			Maths::Vector3f HitPoint;
		};

	public:
		Physics() = delete;

		static RaycastHit Raycast(const Maths::Ray& ray, LayerMask& layerMask = LayerMask());
		static RaycastHit Raycast(const Maths::Ray& ray, int layerMask);

	public:
		static RaycastHit IndividualRaycast(const Maths::Ray& ray, const AABB& aabb, const Maths::Vector3f& worldPosition);
		static RaycastHit IndividualRaycast(const Maths::Ray& ray, const OBB& obb, const Maths::Vector3f& worldPosition);
		static RaycastHit IndividualRaycast(const Maths::Ray& ray, const Maths::Vector3f& min, const Maths::Vector3f& max);

	};

}