#pragma once
#include "Object.h"
#include "Maths\__Maths__.h"
#include "Color.h"

namespace Ablaze
{

	struct Vertex
	{
	public:
		Maths::Vector3f position;
		Maths::Vector3f normal;
		Maths::Vector2f texCoord;
		Color color;
		Maths::Vector3f tangent;

	public:
		Vertex(const Maths::Vector3f& position, const Maths::Vector3f& normal, const Maths::Vector2f& texCoord, const Color& color, const Maths::Vector3f& tangent);

	};

}