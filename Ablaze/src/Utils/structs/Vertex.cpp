#include "Vertex.h"

namespace Ablaze
{

	Vertex::Vertex(const Maths::Vec3& position, const Maths::Vec3& normal, const Maths::Vec2& texCoord, const Color& color, const Maths::Vec3& tangent) : Object(),
		position(position), normal(normal), texCoord(texCoord), color(color), tangent(tangent)
	{

	}

	String Vertex::ToString() const
	{
		return "Vertex";
	}

}