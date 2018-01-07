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

		// Scene Functions

		static RaycastHit Raycast(const Maths::Ray& ray, const LayerMask& layerMask = LayerMask());
		static RaycastHit Raycast(const Maths::Ray& ray, int layerMask);

		static CollisionInfo Intersects(GameObject* object, const LayerMask& layerMask = LayerMask());

	public:
		// Individual Functions

		static bool Contains(const AABB& aabb, const Maths::Vector3f& worldPosition, const Maths::Vector3f& worldPoint);
		static bool Contains(const AABB& aabb, const Maths::Vector3f& worldPosition, const AABB& other, const Maths::Vector3f& otherPosition);
		static bool Intersects(const AABB& aabb, const Maths::Vector3f& worldPosition, const AABB& other, const Maths::Vector3f& otherPosition);

	private:
		static RaycastHit IndividualRaycast(const Maths::Ray& ray, const AABB& aabb, const Maths::Vector3f& worldPosition);
		static RaycastHit IndividualRaycast(const Maths::Ray& ray, const OBB& obb, const Maths::Vector3f& worldPosition);
		static RaycastHit IndividualRaycast(const Maths::Ray& ray, const Maths::Vector3f& min, const Maths::Vector3f& max);

	};

}