#include "Ray.h"

namespace Ablaze
{
	namespace Maths
	{

		Ray::Ray(const Vector3f& origin, const Vector3f& direction)
			: Origin(origin), Direction(direction.Normalize())
		{

		}

		Ray::Ray() : Ray(Maths::Vector3f(0.0f), Maths::Vector3f::Forward())
		{
		
		}

		String Ray::ToString() const
		{
			return "Ray(" + Origin.ToString() + ", " + Direction.ToString() + ")";
		}

		std::ostream& operator<<(std::ostream& stream, const Ray& ray)
		{
			stream << ray.ToString();
			return stream;
		}

	}
}