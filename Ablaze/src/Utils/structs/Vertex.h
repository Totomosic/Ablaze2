#pragma once
#include "AblazeGL.h"
#include "Maths\__Maths__.h"
#include "Object.h"
#include "Color.h"

namespace Ablaze
{

	struct AB_API Vertex : public Object
	{
		Maths::Vec3 position;
		Maths::Vec3 normal;
		Maths::Vec2 texCoord;
		Color color;
		Maths::Vec3 tangent;

		Vertex(const Maths::Vec3& position, const Maths::Vec3& normal, const Maths::Vec2& texCoord, const Color& color, const Maths::Vec3& tangent);
		
		String ToString() const override;
	};

}