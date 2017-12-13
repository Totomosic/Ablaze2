#pragma once
#include "Common.h"

namespace Ablaze
{

	struct AB_API OBB
	{
	public:
		Maths::Vector3f Min;
		Maths::Vector3f Max;
		Maths::Quaternion Orientation;

	public:
		OBB(const Maths::Vector3f& min, const Maths::Vector3f& max, const Maths::Quaternion& orientation = Maths::Quaternion::Identity());
		OBB(const Maths::Vector3f& size, const Maths::Quaternion& orientation = Maths::Quaternion::Identity());
		OBB();

		Maths::Vector3f Size() const;
		float Width() const;
		float Height() const;
		float Depth() const;

		void SetSize(const Maths::Vector3f& size);

	};

}