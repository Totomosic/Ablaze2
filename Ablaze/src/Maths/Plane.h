#pragma once
#include "Vectors\__Vectors__.h"

namespace Ablaze
{
	namespace Maths
	{

		struct AB_API Plane
		{
		public:
			Maths::Vector3f normal;
			float height;

		public:
			Plane();
			Plane(const Maths::Vector3f& normal, float height);
			Plane(float x, float y, float z, float height);

		};

	}
}