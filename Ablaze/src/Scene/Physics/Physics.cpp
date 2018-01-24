#include "Physics.h"
#include "Scene\__Scene__.h"

namespace Ablaze
{

	RaycastHit Physics::Raycast(const Maths::Ray& ray, const LayerMask& mask)
	{
		RaycastHit result;
		result.Ray = ray;
		result.Mask = mask;
		result.DidHit = false;

		std::vector<RaycastPlaceholder> hits;

		for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers(mask))
		{
			for (GameObject* object : layer->GameObjects())
			{
				if (object->HasComponent<Transform>() && object->HasComponent<BoxCollider>())
				{
					OBB box = object->GetComponent<BoxCollider>().Box();
					box.Orientation = object->transform().Rotation();
					RaycastHit thisHit = IndividualRaycast(ray, box, object->transform().Position());
					if (thisHit.DidHit)
					{
						hits.push_back({ object, thisHit.HitLocations[0] });
					}
				}
			}
		}
		std::sort(hits.begin(), hits.end(), [&ray](RaycastPlaceholder& left, RaycastPlaceholder& right)
		{
			return Maths::Vector3f::Distance(ray.Origin, left.HitPoint) < Maths::Vector3f::Distance(ray.Origin, right.HitPoint);
		});
		result.DidHit = hits.size() > 0;
		for (RaycastPlaceholder& p : hits)
		{
			result.GameObjects.push_back(p.Obj);
			result.HitLocations.push_back(p.HitPoint);
		}
		return result;
	}

	RaycastHit Physics::IndividualRaycast(const Maths::Ray& ray, const AABB& aabb, const Maths::Vector3f& worldPosition)
	{
		Maths::Vector3f min = worldPosition + aabb.Min;
		Maths::Vector3f max = worldPosition + aabb.Max;
		return IndividualRaycast(ray, min, max);
	}

	RaycastHit Physics::IndividualRaycast(const Maths::Ray& ray, const OBB& obb, const Maths::Vector3f& worldPosition)
	{
		Maths::Vector3f min = worldPosition + (obb.Orientation * obb.Min);
		Maths::Vector3f max = worldPosition + (obb.Orientation * obb.Max);
		return IndividualRaycast(ray, min, max);
	}

	RaycastHit Physics::IndividualRaycast(const Maths::Ray& ray, const Maths::Vector3f& min, const Maths::Vector3f& max)
	{
		float collLength;
		Maths::Vector3f dirfrac;
		dirfrac.x = 1.0f / ray.Direction.x;
		dirfrac.y = 1.0f / ray.Direction.y;
		dirfrac.z = 1.0f / ray.Direction.z;

		float t1 = (min.x - ray.Origin.x) * dirfrac.x;
		float t2 = (max.x - ray.Origin.x) * dirfrac.x;
		float t3 = (min.y - ray.Origin.y) * dirfrac.y;
		float t4 = (max.y - ray.Origin.y) * dirfrac.y;
		float t5 = (min.z - ray.Origin.z) * dirfrac.z;
		float t6 = (max.z - ray.Origin.z) * dirfrac.z;

		float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
		float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

		// if tmax < 0, ray is intersecting but aabb is behind
		if (tmax < 0)
		{
			collLength = tmax;
			RaycastHit result;
			result.DidHit = false;
			result.Ray = ray;
			return result;
		}

		// if tmin > tmax ray doesnt intersect
		if (tmin > tmax)
		{
			collLength = tmax;
			RaycastHit result;
			result.DidHit = false;
			result.Ray = ray;
			return result;
		}

		collLength = tmin;
		RaycastHit result;
		result.DidHit = true;
		result.Ray = ray;
		result.HitLocations.push_back(ray.Origin + ray.Direction * collLength);
		return result;
	}

}