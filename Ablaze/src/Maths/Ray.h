#pragma once
#include "Vectors\__Vectors__.h"

namespace Ablaze
{
	namespace Maths
	{

		struct AB_API Ray
		{
			Vector3f origin;
			Vector3f direction;

			Ray(const Vector3f& origin, const Vector3f& direction);

			String ToString() const;

			friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);
		};

	}
}