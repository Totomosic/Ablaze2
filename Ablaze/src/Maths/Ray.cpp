#include "Ray.h"

namespace Ablaze
{
	namespace Maths
	{

		Ray::Ray(const Vec3& origin, const Vec3& direction)
			: origin(origin), direction(direction)
		{

		}

		String Ray::ToString() const
		{
			return "Ray(" + origin.ToString() + ", " + direction.ToString() + ")";
		}

		std::ostream& operator<<(std::ostream& stream, const Ray& ray)
		{
			stream << ray.ToString();
			return stream;
		}

	}
}