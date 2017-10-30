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

		Model* Shapes::Ellipse(float width, float height, int vertexCount, const Color& color)
		{
			VertexBuffer* vbo = new VertexBuffer((vertexCount + 1) * sizeof(Vertex), BufferLayout::Vertex());
			IndexBuffer* indexBuffer = new IndexBuffer(3 * (vertexCount) * sizeof(uint));

			Vertex* ptr = (Vertex*)vbo->Map(AccessMode::Write);
			uint* indices = (uint*)indexBuffer->Map(AccessMode::Write);
			// Centre vertex
			ptr->position = Maths::Vec3(0.0f, 0.0f, 0.0f);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vec2(0.5f, 0.5f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			for (int i = 0; i < vertexCount; i++)
			{
				float cosx = (float)cos(Maths::PI * 2.0 / vertexCount * i);
				float sinx = (float)sin(Maths::PI * 2.0 / vertexCount * i);
				float x = cosx * width / 2.0f;
				float y = sinx * height / 2.0f;
				ptr->position = Maths::Vec3(x, y, 0.0f);
				ptr->normal = Maths::Vec3(0.0f, 0.0f, 1.0f);
				ptr->texCoord = Maths::Vec2(cosx / 2.0f + 0.5f, sinx / 2.0f + 0.5f);
				ptr->color = color;
				ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
				ptr++;

				*indices = 0;
				indices++;
				*indices = i + 1;
				indices++;
				if (i == vertexCount - 1)
				{
					*indices = 1;
				}
				else
				{
					*indices = i + 2;
				}
				indices++;
			}
			
			indexBuffer->Unmap();
			vbo->Unmap();

			VertexArray* vao = new VertexArray(indexBuffer);
			vao->AddVertexBuffer(vbo);
			return new Model(vao);
		}

	}
}