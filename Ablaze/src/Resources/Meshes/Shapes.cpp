#include "Shapes.h"

namespace Ablaze
{
	namespace Internal
	{

		Model* Shapes::Rectangle(float width, float height, const Color& color)
		{
			VertexArray* vao = new VertexArray;
			uint* indices = new uint[6]{ 0, 1, 2, 0, 2, 3 };
			VertexBuffer* vbo = vao->CreateAttribute(4 * sizeof(Vertex), BufferLayout::Vertex());
			IndexBuffer* indexBuffer = vao->CreateIndexBuffer(indices, 6 * sizeof(uint));
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

			return new Model(vao);
		}

		Model* Shapes::Ellipse(float width, float height, int vertexCount, const Color& color)
		{
			VertexArray* vao = new VertexArray;
			VertexBuffer* vbo = vao->CreateAttribute((vertexCount + 1) * sizeof(Vertex), BufferLayout::Vertex());
			IndexBuffer* indexBuffer = vao->CreateIndexBuffer(3 * (vertexCount) * sizeof(uint));

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

			return new Model(vao);
		}

		Model* Shapes::Cuboid(float width, float height, float depth, const Color& color)
		{
			float x = width / 2.0f;
			float y = height / 2.0f;
			float z = depth / 2.0f;

			VertexArray* vao = new VertexArray;
			VertexBuffer* vbo = vao->CreateAttribute(24 * sizeof(Vertex), BufferLayout::Vertex());
			//                                 Front                 Back                      Left                     Right                    Top                     Bottom
			uint* indices = new uint[36]{ 0, 3, 6, 0, 6, 9,   12, 15, 18, 12, 18, 21,   22, 19, 4, 22, 4, 1,   10, 7, 16, 10, 16, 13,   23, 2, 11, 23, 11, 14,   5, 20, 8, 20, 17, 8 };
			vao->CreateIndexBuffer(indices, 36 * sizeof(uint));
			delete[] indices;

			Vertex* ptr = (Vertex*)vbo->Map(AccessMode::Write);

			// Top Left Front - Front (0)
			ptr->position = Maths::Vec3(-x, y, z);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Front - Left (1)
			ptr->position = Maths::Vec3(-x, y, z);
			ptr->normal = Maths::Vec3(-1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Front - Top (2)
			ptr->position = Maths::Vec3(-x, y, z);
			ptr->normal = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Front - Front (3)
			ptr->position = Maths::Vec3(-x, -y, z);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Front - Left (4)
			ptr->position = Maths::Vec3(-x, -y, z);
			ptr->normal = Maths::Vec3(-1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Front - Bottom (5)
			ptr->position = Maths::Vec3(-x, -y, z);
			ptr->normal = Maths::Vec3(0.0f, -1.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Front - Front (6)
			ptr->position = Maths::Vec3(x, -y, z);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Front - Right (7)
			ptr->position = Maths::Vec3(x, -y, z);
			ptr->normal = Maths::Vec3(1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Front - Bottom (8)
			ptr->position = Maths::Vec3(x, -y, z);
			ptr->normal = Maths::Vec3(0.0f, -1.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Front - Front (9)
			ptr->position = Maths::Vec3(x, y, z);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Front - Right (10)
			ptr->position = Maths::Vec3(x, y, z);
			ptr->normal = Maths::Vec3(1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Front - Top (11)
			ptr->position = Maths::Vec3(x, y, z);
			ptr->normal = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Back - Back (12)
			ptr->position = Maths::Vec3(x, y, -z);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, -1.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Back - Right (13)
			ptr->position = Maths::Vec3(x, y, -z);
			ptr->normal = Maths::Vec3(1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Back - Top (14)
			ptr->position = Maths::Vec3(x, y, -z);
			ptr->normal = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Back - Back (15)
			ptr->position = Maths::Vec3(x, -y, -z);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, -1.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Back - Right (16)
			ptr->position = Maths::Vec3(x, -y, -z);
			ptr->normal = Maths::Vec3(1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Back - Bottom (17)
			ptr->position = Maths::Vec3(x, -y, -z);
			ptr->normal = Maths::Vec3(0.0f, -1.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Back - Back (18)
			ptr->position = Maths::Vec3(-x, -y, -z);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, -1.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Back - Left (19)
			ptr->position = Maths::Vec3(-x, -y, -z);
			ptr->normal = Maths::Vec3(-1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Back - Bottom (20)
			ptr->position = Maths::Vec3(-x, -y, -z);
			ptr->normal = Maths::Vec3(0.0f, -1.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Back - Back (21)
			ptr->position = Maths::Vec3(-x, y, -z);
			ptr->normal = Maths::Vec3(0.0f, 0.0f, -1.0f);
			ptr->texCoord = Maths::Vec2(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Back - Left (22)
			ptr->position = Maths::Vec3(-x, y, -z);
			ptr->normal = Maths::Vec3(-1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Back - Top (23)
			ptr->position = Maths::Vec3(-x, y, -z);
			ptr->normal = Maths::Vec3(0.0f, 1.0f, 0.0f);
			ptr->texCoord = Maths::Vec2(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vec3(0.0f, 1.0f, 0.0f);

			vbo->Unmap();

			return new Model(vao);
		}

		Model* Shapes::Grid(float width, float depth, int xVertices, int zVertices, const Color& color)
		{
			if (xVertices < 2 || zVertices < 2)
			{
				AB_ERROR("Grid could not be constructed, xVertices and zVertices must be >= 2, xVertices: " + std::to_string(xVertices) + " zVertices: " + std::to_string(zVertices));
				return nullptr;
			}
			VertexArray* vao = new VertexArray;
			VertexBuffer* vbo = vao->CreateAttribute(xVertices * zVertices * sizeof(Vertex), BufferLayout::Vertex());
			IndexBuffer* ibo = vao->CreateIndexBuffer((xVertices - 1) * (zVertices - 1) * 6 * sizeof(uint));

			Vertex* ptr = (Vertex*)vbo->Map(AccessMode::Write);
			uint* indices = (uint*)ibo->Map(AccessMode::Write);

			int index = 0;
			for (int i = 0; i < zVertices; i++)
			{
				for (int j = 0; j < xVertices; j++)
				{
					ptr->position = Maths::Vec3(-width / 2.0f + j * (width / (float)(xVertices - 1)), 0, -depth / 2.0f + i * (width / (float)(zVertices - 1)));
					ptr->normal = Maths::Vec3(0.0f, 1.0f, 0.0f);
					ptr->texCoord = Maths::Vec2((float)j / (xVertices - 1), 1.0f - (float)i / (zVertices - 1));
					ptr->color = color;
					ptr->tangent = Maths::Vec3(0.0, 0.0, -1.0);
					ptr++;

					if (j != xVertices - 1 && i != zVertices - 1)
					{
						*(indices++) = index;
						*(indices++) = index + xVertices;
						*(indices++) = index + xVertices + 1;
						*(indices++) = index;
						*(indices++) = index + xVertices + 1;
						*(indices++) = index + 1;
					}

					index++;
				}
			}

			ibo->Unmap();
			vbo->Unmap();
			return new Model(vao);
		}

	}
}