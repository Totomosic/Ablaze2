#pragma once
#include "Common.h"
#include "Scene\Physics\__Physics__.h"
#include "Scene\GameObject.h"

namespace Ablaze
{

	class AB_API OctreeNode : public Object
	{
	private:
		static const int SUBDIVISION_COUNT = 8;

	private:
		int m_MaxObjectsBeforeSub;
		Maths::Vector3f m_Position;
		AABB m_Bounds;

		std::vector<GameObject*> m_Objects;
		bool m_HasChildren;
		OctreeNode** m_Children;

	public:
		OctreeNode(const Maths::Vector3f& position, const AABB& bounds, int maxObjects);

		int MaxObjectsBeforeSub() const;
		int ObjectCount() const;
		bool HasChildren() const;
		OctreeNode** Children() const;
		const std::vector<GameObject*>& Objects() const;
		const Maths::Vector3f& Position() const;
		const AABB& Bounds() const;
		bool ContainsGameObject(GameObject* object) const;

		void AddGameObject(GameObject* object);
		void RemoveGameObject(GameObject* object);
		void Subdivide();

		String ToString() const override;

	private:
		bool AddObjectToChild(GameObject* object) const;
		bool ObjectIsCompletelyWithin(GameObject* object) const;

	};

}