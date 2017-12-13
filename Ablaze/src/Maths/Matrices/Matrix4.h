#pragma once
#include "Maths\Vectors\__Vectors__.h"
#include "Matrix4Template.h"

namespace Ablaze
{
	namespace Maths
	{
		struct AB_API Matrix4f
		{
			AB_MATHS_MATRIX4_CLASS_TEMPLATE_HEADER(Matrix4f, float, Vector4f, Vector3f, Vector2f);
		};

		struct AB_API Matrix4i
		{
			AB_MATHS_MATRIX4_CLASS_TEMPLATE_HEADER(Matrix4i, int, Vector4i, Vector3i, Vector2i);
		};

		struct AB_API Matrix4d
		{
			AB_MATHS_MATRIX4_CLASS_TEMPLATE_HEADER(Matrix4d, double, Vector4f, Vector3f, Vector2f);
		};
	}
}