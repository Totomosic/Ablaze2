#include "OBB.h"

namespace Ablaze
{

	OBB::OBB(const Maths::Vector3f& min, const Maths::Vector3f& max, const Maths::Quaternion& orientation)
		: Min(min), Max(max), Orientation(orientation)
	{
		
	}

	OBB::OBB(const Maths::Vector3f& size, const Maths::Quaternion& orientation) : OBB(-size / 2.0f, size / 2.0f, orientation)
	{
	
	}

	OBB::OBB() : OBB(Maths::Vector3f(1.0f, 1.0f, 1.0f))
	{
	
	}

	Maths::Vector3f OBB::Size() const
	{
		return Max - Min;
	}

	float OBB::Width() const
	{
		return Size().x;
	}

	float OBB::Height() const
	{
		return Size().y;
	}

	float OBB::Depth() const
	{
		return Size().z;
	}

	void OBB::SetSize(const Maths::Vector3f& size)
	{
		Min = -size / 2.0f;
		Max = size / 2.0f;
	}

}