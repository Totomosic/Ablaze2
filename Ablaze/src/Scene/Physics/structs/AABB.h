#pragma once
#include "Common.h"

namespace Ablaze
{

	struct AB_API AABB
	{
	public:
		Maths::Vector3f Min;
		Maths::Vector3f Max;

	public:
		AABB(const Maths::Vector3f& min, const Maths::Vector3f& max);
		AABB(const Maths::Vector3f& size);
		AABB();

		Maths::Vector3f Size() const;
		float Width() const;
		float Height() const;
		float Depth() const;

		void SetSize(const Maths::Vector3f& size);

	};

}