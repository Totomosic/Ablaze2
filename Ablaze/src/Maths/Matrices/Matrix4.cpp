#include "Matrix4.h"
#include "Logging.h"

namespace Ablaze
{
	namespace Maths
	{
		AB_MATHS_MATRIX4_CLASS_TEMPLATE_CPP(Matrix4f, float, Vector4f, Vector3f, Vector2f);
		AB_MATHS_MATRIX4_CLASS_TEMPLATE_CPP(Matrix4i, int, Vector4i, Vector3i, Vector2i);
		AB_MATHS_MATRIX4_CLASS_TEMPLATE_CPP(Matrix4d, double, Vector4f, Vector3f, Vector2f);
	}
}