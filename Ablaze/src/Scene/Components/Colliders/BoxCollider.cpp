#include "BoxCollider.h"

namespace Ablaze
{

	BoxCollider::BoxCollider(const OBB& boundingBox) : Component(),
		m_BoundingBox(boundingBox)
	{
	
	}

	const OBB& BoxCollider::Box() const
	{
		return m_BoundingBox;
	}

	OBB& BoxCollider::Box()
	{
		return m_BoundingBox;
	}

	Component* BoxCollider::Clone() const
	{
		BoxCollider* b = new BoxCollider(m_BoundingBox);
		return b;
	}

	String BoxCollider::ToString() const
	{
		return "BoxCollider";
	}

}