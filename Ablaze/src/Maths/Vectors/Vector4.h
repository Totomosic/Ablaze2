#pragma once
#include "Vector4Template.h"
#include "Vector3.h"

namespace Ablaze
{
	namespace Maths
	{
		struct AB_API Vector4f
		{		
			AB_MATHS_VECTOR4_CLASS_TEMPLATE_HEADER(Vector4f, float, Vector3f, Vector2f);
		};	

		struct AB_API Vector4i
		{
			AB_MATHS_VECTOR4_CLASS_TEMPLATE_HEADER(Vector4i, int, Vector3i, Vector2i);
		};
	}
}