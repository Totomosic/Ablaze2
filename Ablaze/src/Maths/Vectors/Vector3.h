#pragma once
#include "Vector3Template.h"
#include "Vector2.h"

namespace Ablaze
{
	namespace Maths
	{
		struct AB_API Vector3f
		{
			AB_MATHS_VECTOR3_CLASS_TEMPLATE_HEADER(Vector3f, float, Vector2f);
		};

		struct AB_API Vector3i
		{
			AB_MATHS_VECTOR3_CLASS_TEMPLATE_HEADER(Vector3i, int, Vector2i);
		};
	}
}