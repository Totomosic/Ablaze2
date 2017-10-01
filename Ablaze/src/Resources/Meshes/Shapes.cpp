#include "Shapes.h"

namespace Ablaze
{
	namespace Internal
	{

		Model* Shapes::Rectangle(float width, float height, const Color& color)
		{
			uint* indices = new uint[6]{ 0, 1, 2, 0, 2, 3 };
			VertexBuffer* vbo = new VertexBuffer(4 * sizeof(Vertex), BufferLayout::Vertex());
			IndexBuffer* indexBuffer = new IndexBuffer(indices, 6 * sizeof(uint));
			delete[] indices;

			Vertex* ptr = (Vertex*)vbo->Map(AccessMode::Write);

			ptr->position = Maths::Vec3(-width / 2.0f, height / 2.0f, 0);
			ptr->normal = Maths::Vec3(0, 0, 1);
			ptr->texCoord = Maths::Vec2(0, 1);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0, 1, 0);
			ptr++;

			ptr->position = Maths::Vec3(-width / 2.0f, -height / 2.0f, 0);
			ptr->normal = Maths::Vec3(0, 0, 1);
			ptr->texCoord = Maths::Vec2(0, 0);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0, 1, 0);
			ptr++;

			ptr->position = Maths::Vec3(width / 2.0f, -height / 2.0f, 0);
			ptr->normal = Maths::Vec3(0, 0, 1);
			ptr->texCoord = Maths::Vec2(1, 0);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0, 1, 0);
			ptr++;

			ptr->position = Maths::Vec3(width / 2.0f, height / 2.0f, 0);
			ptr->normal = Maths::Vec3(0, 0, 1);
			ptr->texCoord = Maths::Vec2(1, 1);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0, 1, 0);
			
			vbo->Unmap();

			VertexArray* vao = new VertexArray(indexBuffer);
			vao->AddVertexBuffer(vbo);
			return new Model(vao);
		}

	}
}