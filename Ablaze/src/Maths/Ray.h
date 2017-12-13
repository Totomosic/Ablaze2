#pragma once
#include "Vectors\__Vectors__.h"

namespace Ablaze
{
	namespace Maths
	{

		struct AB_API Ray
		{
		public:
			Vector3f Origin;
			Vector3f Direction;

		public:
			Ray(const Vector3f& origin, const Vector3f& direction);
			Ray();

			String ToString() const;
			friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);
		};

	}
}