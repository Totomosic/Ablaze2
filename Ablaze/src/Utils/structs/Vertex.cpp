#include "Vertex.h"

namespace Ablaze
{

	Vertex::Vertex(const Maths::Vec3& position, const Maths::Vec3& normal, const Maths::Vec2& texCoord, const Color& color, const Maths::Vec3& tangent)
	{
		this->position = position;
		this->normal = normal;
		this->texCoord = texCoord;
		this->color = color;
		this->tangent = tangent;
	}

}