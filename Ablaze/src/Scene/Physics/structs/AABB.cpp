#include "AABB.h"

namespace Ablaze
{

	AABB::AABB(const Maths::Vector3f& min, const Maths::Vector3f& max)
		: Min(min), Max(max)
	{
	
	}

	AABB::AABB(const Maths::Vector3f& size) : AABB(-size / 2.0f, size / 2.0f)
	{
	
	}

	AABB::AABB() : AABB(Maths::Vector3f(1.0f, 1.0f, 1.0f))
	{
	
	}

	Maths::Vector3f AABB::Size() const
	{
		return Max - Min;
	}

	float AABB::Width() const
	{
		return Size().x;
	}

	float AABB::Height() const
	{
		return Size().y;
	}

	float AABB::Depth() const
	{
		return Size().z;
	}

	void AABB::SetSize(const Maths::Vector3f& size)
	{
		Min = -size / 2.0f;
		Max = size / 2.0f;
	}

}