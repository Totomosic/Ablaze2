#pragma once
#include "Vec3.h"

namespace Ablaze
{
	namespace Maths
	{

		struct AB_API Ray
		{
			Vec3 origin;
			Vec3 direction;

			Ray(const Vec3& origin, const Vec3& direction);

			String ToString() const;

			friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);
		};

	}
}