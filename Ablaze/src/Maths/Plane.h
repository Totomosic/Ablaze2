#pragma once
#include "Vec3.h"

namespace Ablaze
{
	namespace Maths
	{

		struct AB_API Plane
		{
			Maths::Vec3 normal;
			float height;

			Plane();
			Plane(const Maths::Vec3& normal, float height);
			Plane(float x, float y, float z, float height);
		};

	}
}