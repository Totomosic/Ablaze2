#include "OctreeNode.h"
#include "Scene\Components\__Components__.h"

namespace Ablaze
{

	OctreeNode::OctreeNode(const Maths::Vector3f& position, const AABB& bounds, int maxObjects) : Object(),
		m_MaxObjectsBeforeSub(maxObjects), m_Position(position), m_Bounds(bounds), m_Objects(), m_HasChildren(false), m_Children()
	{
	
	}

	int OctreeNode::MaxObjectsBeforeSub() const
	{
		return m_MaxObjectsBeforeSub;
	}

	int OctreeNode::ObjectCount() const
	{
		return m_Objects.size();
	}

	bool OctreeNode::HasChildren() const
	{
		return m_HasChildren;
	}

	OctreeNode** OctreeNode::Children() const
	{
		return m_Children;
	}

	const std::vector<GameObject*>& OctreeNode::Objects() const
	{
		return m_Objects;
	}

	const Maths::Vector3f& OctreeNode::Position() const
	{
		return m_Position;
	}

	const AABB& OctreeNode::Bounds() const
	{
		return m_Bounds;
	}

	bool OctreeNode::ContainsGameObject(GameObject* object) const
	{
		return std::find(m_Objects.begin(), m_Objects.end(), object) != m_Objects.end();
	}

	void OctreeNode::AddGameObject(GameObject* object)
	{
		if (!HasChildren())
		{
			m_Objects.push_back(object);
			if (ObjectCount() > m_MaxObjectsBeforeSub)
			{
				Subdivide();
			}
		}
		else
		{
			// Determine which child to add it to
			if (!AddObjectToChild(object))
			{
				m_Objects.push_back(object);
			}
		}
	}

	void OctreeNode::RemoveGameObject(GameObject* object)
	{
		if (!HasChildren())
		{
			AB_ASSERT(ContainsGameObject(object), "Object was not found");
			auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
			m_Objects.erase(it);
		}
		else
		{
			// Determine which child to remove it from
		}
	}

	void OctreeNode::Subdivide()
	{
		AB_ASSERT(!HasChildren(), "Node has already been subdivided");
		m_HasChildren = true;

		AABB newBounds = AABB(m_Bounds.Size() / 2.0f);
		Maths::Vector3f quartSize = m_Bounds.Size() / 4.0f;

		Maths::Vector3f blf = m_Position + Maths::Vector3f(-quartSize.x, -quartSize.y, quartSize.z);
		Maths::Vector3f brf = m_Position + Maths::Vector3f(quartSize.x, -quartSize.y, quartSize.z);
		Maths::Vector3f blb = m_Position + Maths::Vector3f(-quartSize.x, -quartSize.y, -quartSize.z);
		Maths::Vector3f brb = m_Position + Maths::Vector3f(quartSize.x, -quartSize.y, -quartSize.z);
		Maths::Vector3f tlf = m_Position + Maths::Vector3f(-quartSize.x, quartSize.y, quartSize.z);
		Maths::Vector3f trf = m_Position + Maths::Vector3f(quartSize.x, quartSize.y, quartSize.z);
		Maths::Vector3f tlb = m_Position + Maths::Vector3f(-quartSize.x, quartSize.y, -quartSize.z);
		Maths::Vector3f trb = m_Position + Maths::Vector3f(quartSize.x, quartSize.y, -quartSize.z);

		m_Children = new OctreeNode*[SUBDIVISION_COUNT];
		m_Children[0] = new OctreeNode(blf, newBounds, m_MaxObjectsBeforeSub);
		m_Children[1] = new OctreeNode(brf, newBounds, m_MaxObjectsBeforeSub);
		m_Children[2] = new OctreeNode(blb, newBounds, m_MaxObjectsBeforeSub);
		m_Children[3] = new OctreeNode(brb, newBounds, m_MaxObjectsBeforeSub);
		m_Children[4] = new OctreeNode(tlf, newBounds, m_MaxObjectsBeforeSub);
		m_Children[5] = new OctreeNode(trf, newBounds, m_MaxObjectsBeforeSub);
		m_Children[6] = new OctreeNode(tlb, newBounds, m_MaxObjectsBeforeSub);
		m_Children[7] = new OctreeNode(trb, newBounds, m_MaxObjectsBeforeSub);

		std::vector<GameObject*> couldntBeAdded;
		for (GameObject* object : m_Objects)
		{
			if (!AddObjectToChild(object))
			{
				couldntBeAdded.push_back(object);
			}
		}
		m_Objects.clear();
		for (GameObject* object : couldntBeAdded)
		{
			m_Objects.push_back(object);
		}

	}

	String OctreeNode::ToString() const
	{
		return "OctreeNode";
	}

	bool OctreeNode::AddObjectToChild(GameObject* object) const
	{
		AB_ASSERT(HasChildren(), "No children to add to");
		for (int i = 0; i < 8; i++)
		{
			if (m_Children[i]->ObjectIsCompletelyWithin(object))
			{
				m_Children[i]->AddGameObject(object);
				return true;
			}
		}
		return false;
	}

	bool OctreeNode::ObjectIsCompletelyWithin(GameObject* object) const
	{
		if (object->HasComponent<BoxCollider>())
		{

		}
		return true;
	}

}