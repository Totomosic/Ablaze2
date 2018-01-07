#pragma once
#include "Common.h"
#include "Scene\Physics\__Physics__.h"

namespace Ablaze
{

	class GameObject;
	class LayerMask;

	class AB_API SceneGraph : public Object
	{
	public:
		virtual std::vector<GameObject*> GetAll(const LayerMask& mask) const = 0;
		virtual std::vector<GameObject*> GetAll() const = 0;

		virtual std::vector<GameObject*> FindAllNearTo(const Maths::Vector3f& position, float maxDistance, const LayerMask& mask) const = 0;
		virtual std::vector<GameObject*> FindAllNearTo(const Maths::Vector3f& position, float maxDistance) const = 0;
		virtual std::vector<GameObject*> FindKNearestTo(const Maths::Vector3f& position, int maxCount, const LayerMask& mask) const = 0;
		virtual std::vector<GameObject*> FindKNearestTo(const Maths::Vector3f& position, int maxCount) const = 0;
		virtual GameObject* FindNearestTo(const Maths::Vector3f& position, const LayerMask& mask) const = 0;
		virtual GameObject* FindNearestTo(const Maths::Vector3f& position) const = 0;

		virtual std::vector<GameObject*> Select(const Maths::Vector3f& position, const AABB& bounds, const LayerMask& mask) const = 0;
		virtual std::vector<GameObject*> Select(const Maths::Vector3f& position, const AABB& bounds) const = 0;

		virtual std::vector<GameObject*> TestCull(GameObject* camera, const LayerMask& mask) const = 0;
		virtual std::vector<GameObject*> TestCull(GameObject* camera) const = 0;
		virtual std::vector<GameObject*> TestClip(const Maths::Plane& plane, const LayerMask& mask) const = 0;
		virtual std::vector<GameObject*> TestClip(const Maths::Plane& plane) const = 0;

		virtual void AddGameObject(GameObject* object) = 0;
		virtual void RemoveGameObject(GameObject* object) = 0;
		virtual int ObjectCount() const = 0;

	};

}