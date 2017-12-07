#pragma once
#include "Vector2Template.h"
#include "Logging.h"

namespace Ablaze
{
	namespace Maths
	{
		struct AB_API Vector2f
		{
			AB_MATHS_VECTOR2_CLASS_TEMPLATE_HEADER(Vector2f, float);
		};

		struct AB_API Vector2i
		{
			AB_MATHS_VECTOR2_CLASS_TEMPLATE_HEADER(Vector2i, int);
		};
	}
}