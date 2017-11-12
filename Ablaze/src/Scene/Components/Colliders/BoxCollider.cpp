#include "BoxCollider.h"

namespace Ablaze
{

	BoxCollider::BoxCollider(const Maths::Vec3& size, const Transform& transform) : Component(),
		m_Size(size), m_Transform(transform)
	{
	
	}

	BoxCollider::BoxCollider(const Maths::Vec3& size) : BoxCollider(size, Transform())
	{
	
	}

	BoxCollider::BoxCollider() : BoxCollider(Maths::Vec3(1.0f))
	{
		
	}

	const Maths::Vec3& BoxCollider::Size() const
	{
		return m_Size;
	}

	Maths::Vec3& BoxCollider::Size()
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

	Maths::Vec3 BoxCollider::Max() const
	{
		return Size() / 2;
	}

	Maths::Vec3 BoxCollider::Min() const
	{
		return -Size() / 2;
	}

	Endpoint* BoxCollider::Endpoints()
	{
		Maths::Vec3 min = Min();
		Maths::Vec3 max = Max();
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