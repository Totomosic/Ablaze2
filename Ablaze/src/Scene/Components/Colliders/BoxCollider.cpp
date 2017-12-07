#include "BoxCollider.h"

namespace Ablaze
{

	BoxCollider::BoxCollider(const Maths::Vector3f& size, const Transform& transform) : Component(),
		m_Size(size), m_Transform(transform)
	{
	
	}

	BoxCollider::BoxCollider(const Maths::Vector3f& size) : BoxCollider(size, Transform())
	{
	
	}

	BoxCollider::BoxCollider() : BoxCollider(Maths::Vector3f(1.0f))
	{
		
	}

	const Maths::Vector3f& BoxCollider::Size() const
	{
		return m_Size;
	}

	Maths::Vector3f& BoxCollider::Size()
	{
		return m_Size;
	}

	const Transform& BoxCollider::transform() const
	{
		return m_Transform;
	}

	Transform& BoxCollider::transform()
	{
		return m_Transform;
	}

	Maths::Vector3f BoxCollider::Max() const
	{
		return Size() / 2;
	}

	Maths::Vector3f BoxCollider::Min() const
	{
		return -Size() / 2;
	}

	Endpoint* BoxCollider::Endpoints()
	{
		Maths::Vector3f min = Min();
		Maths::Vector3f max = Max();
		Endpoint* endpoints = new Endpoint[6];
		endpoints[0] = { this, min.x, true };
		endpoints[1] = { this, min.y, true };
		endpoints[2] = { this, min.z, true };
		endpoints[3] = { this, max.x, false };
		endpoints[4] = { this, max.y, false };
		endpoints[5] = { this, max.z, false };
		return endpoints;
	}

	String BoxCollider::ToString() const
	{
		return "BoxCollider";
	}

	Component* BoxCollider::Clone() const
	{
		BoxCollider* collider = new BoxCollider(m_Size, m_Transform);
		return collider;
	}

}