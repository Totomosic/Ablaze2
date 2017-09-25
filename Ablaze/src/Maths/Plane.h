#pragma once
#include "Vec3.h"

namespace Ablaze
{
	namespace Maths
	{

		struct AB_API Plane
		{
		public:
			Maths::Vec3 normal;
			float height;

		public:
			Plane();
			Plane(const Maths::Vec3& normal, float height);
			Plane(float x, float y, float z, float height);

		};

	}
}