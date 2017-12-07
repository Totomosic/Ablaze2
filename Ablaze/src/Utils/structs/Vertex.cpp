#include "Vertex.h"

namespace Ablaze
{

	Vertex::Vertex(const Maths::Vector3f& position, const Maths::Vector3f& normal, const Maths::Vector2f& texCoord, const Color& color, const Maths::Vector3f& tangent)
	{
		this->position = position;
		this->normal = normal;
		this->texCoord = texCoord;
		this->color = color;
		this->tangent = tangent;
	}

}