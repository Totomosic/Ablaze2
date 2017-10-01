#pragma once
#include "Object.h"
#include "Maths\__Maths__.h"
#include "Color.h"

namespace Ablaze
{

	struct Vertex
	{
	public:
		Maths::Vec3 position;
		Maths::Vec3 normal;
		Maths::Vec2 texCoord;
		Color color;
		Maths::Vec3 tangent;

	public:
		Vertex(const Maths::Vec3& position, const Maths::Vec3& normal, const Maths::Vec2& texCoord, const Color& color, const Maths::Vec3& tangent);

	};

}