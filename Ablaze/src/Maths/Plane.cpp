#include "Plane.h"

namespace Ablaze
{
	namespace Maths
	{

		Plane::Plane(const Maths::Vector3f& normal, float height)
			: normal(normal), height(height)
		{
		
		}

		Plane::Plane(float x, float y, float z, float height) : Plane(Maths::Vector3f(x, y, z), height)
		{
			
		}

		Plane::Plane() : Plane(0, 1, 0, 0)
		{
		
		}

	}
}