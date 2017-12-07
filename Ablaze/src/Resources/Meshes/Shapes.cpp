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

			ptr->position = Maths::Vector3f(-width / 2.0f, height / 2.0f, 0);
			ptr->normal = Maths::Vector3f(0, 0, 1);
			ptr->texCoord = Maths::Vector2f(0, 1);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0, 1, 0);
			ptr++;

			ptr->position = Maths::Vector3f(-width / 2.0f, -height / 2.0f, 0);
			ptr->normal = Maths::Vector3f(0, 0, 1);
			ptr->texCoord = Maths::Vector2f(0, 0);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0, 1, 0);
			ptr++;

			ptr->position = Maths::Vector3f(width / 2.0f, -height / 2.0f, 0);
			ptr->normal = Maths::Vector3f(0, 0, 1);
			ptr->texCoord = Maths::Vector2f(1, 0);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0, 1, 0);
			ptr++;

			ptr->position = Maths::Vector3f(width / 2.0f, height / 2.0f, 0);
			ptr->normal = Maths::Vector3f(0, 0, 1);
			ptr->texCoord = Maths::Vector2f(1, 1);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0, 1, 0);
			
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
			ptr->position = Maths::Vector3f(0.0f, 0.0f, 0.0f);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vector2f(0.5f, 0.5f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			for (int i = 0; i < vertexCount; i++)
			{
				float cosx = (float)cos(Maths::PI * 2.0 / vertexCount * i);
				float sinx = (float)sin(Maths::PI * 2.0 / vertexCount * i);
				float x = cosx * width / 2.0f;
				float y = sinx * height / 2.0f;
				ptr->position = Maths::Vector3f(x, y, 0.0f);
				ptr->normal = Maths::Vector3f(0.0f, 0.0f, 1.0f);
				ptr->texCoord = Maths::Vector2f(cosx / 2.0f + 0.5f, sinx / 2.0f + 0.5f);
				ptr->color = color;
				ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
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

			Vertex* ptr = vbo->Map<Vertex>(AccessMode::Write);

			// Top Left Front - Front (0)
			ptr->position = Maths::Vector3f(-x, y, z);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Front - Left (1)
			ptr->position = Maths::Vector3f(-x, y, z);
			ptr->normal = Maths::Vector3f(-1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Front - Top (2)
			ptr->position = Maths::Vector3f(-x, y, z);
			ptr->normal = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Front - Front (3)
			ptr->position = Maths::Vector3f(-x, -y, z);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Front - Left (4)
			ptr->position = Maths::Vector3f(-x, -y, z);
			ptr->normal = Maths::Vector3f(-1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Front - Bottom (5)
			ptr->position = Maths::Vector3f(-x, -y, z);
			ptr->normal = Maths::Vector3f(0.0f, -1.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Front - Front (6)
			ptr->position = Maths::Vector3f(x, -y, z);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Front - Right (7)
			ptr->position = Maths::Vector3f(x, -y, z);
			ptr->normal = Maths::Vector3f(1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Front - Bottom (8)
			ptr->position = Maths::Vector3f(x, -y, z);
			ptr->normal = Maths::Vector3f(0.0f, -1.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Front - Front (9)
			ptr->position = Maths::Vector3f(x, y, z);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, 1.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Front - Right (10)
			ptr->position = Maths::Vector3f(x, y, z);
			ptr->normal = Maths::Vector3f(1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Front - Top (11)
			ptr->position = Maths::Vector3f(x, y, z);
			ptr->normal = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Back - Back (12)
			ptr->position = Maths::Vector3f(x, y, -z);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, -1.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Back - Right (13)
			ptr->position = Maths::Vector3f(x, y, -z);
			ptr->normal = Maths::Vector3f(1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Right Back - Top (14)
			ptr->position = Maths::Vector3f(x, y, -z);
			ptr->normal = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Back - Back (15)
			ptr->position = Maths::Vector3f(x, -y, -z);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, -1.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Back - Right (16)
			ptr->position = Maths::Vector3f(x, -y, -z);
			ptr->normal = Maths::Vector3f(1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Right Back - Bottom (17)
			ptr->position = Maths::Vector3f(x, -y, -z);
			ptr->normal = Maths::Vector3f(0.0f, -1.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Back - Back (18)
			ptr->position = Maths::Vector3f(-x, -y, -z);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, -1.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Back - Left (19)
			ptr->position = Maths::Vector3f(-x, -y, -z);
			ptr->normal = Maths::Vector3f(-1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 0.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Bottom Left Back - Bottom (20)
			ptr->position = Maths::Vector3f(-x, -y, -z);
			ptr->normal = Maths::Vector3f(0.0f, -1.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Back - Back (21)
			ptr->position = Maths::Vector3f(-x, y, -z);
			ptr->normal = Maths::Vector3f(0.0f, 0.0f, -1.0f);
			ptr->texCoord = Maths::Vector2f(1.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Back - Left (22)
			ptr->position = Maths::Vector3f(-x, y, -z);
			ptr->normal = Maths::Vector3f(-1.0f, 0.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr++;

			// Top Left Back - Top (23)
			ptr->position = Maths::Vector3f(-x, y, -z);
			ptr->normal = Maths::Vector3f(0.0f, 1.0f, 0.0f);
			ptr->texCoord = Maths::Vector2f(0.0f, 1.0f);
			ptr->color = color;
			ptr->tangent = Maths::Vector3f(0.0f, 1.0f, 0.0f);

			vbo->Unmap();

			return new Model(vao);
		}
		
		Model* Shapes::Sphere(float radius, int vertexSpacing, const Color& color)
		{
			VertexArray* vao = new VertexArray;
			VertexBuffer* vbo = vao->CreateAttribute((4 * (180 / vertexSpacing + 1) * ((360 - vertexSpacing) / vertexSpacing + 1)) * sizeof(Vertex), BufferLayout::Vertex());
			IndexBuffer* indexBuffer = vao->CreateIndexBuffer((4 * (180 / vertexSpacing + 1) * ((360 - vertexSpacing) / vertexSpacing + 1)) * sizeof(uint));

			float space = vertexSpacing;
			Vertex* ptr = (Vertex*)vbo->Map(AccessMode::Write);
			uint* indices = (uint*)indexBuffer->Map(AccessMode::Write);
			uint currentVertex = 0;

			for (float b = 0; b <= 180; b += space)
			{
				for (float a = 0; a <= 360 - space; a += space)
				{
					Maths::Vector3f v0 = Maths::Vector3f((float)(radius * sin(ToRadians(a)) * sin(ToRadians(b))), (float)(radius * cos(ToRadians(a)) * sin(ToRadians(b))), (float)(radius * cos(ToRadians(b))));
					Maths::Vector2f tex0 = Maths::Vector2f((b) / 360.0f, (a) / 360.0f);

					Maths::Vector3f v1 = Maths::Vector3f((float)(radius * sin(ToRadians(a)) * sin(ToRadians(b - space))), (float)(radius * cos(ToRadians(a)) * sin(ToRadians(b - space))), (float)(radius * cos(ToRadians(b - space))));
					Maths::Vector2f tex1 = Maths::Vector2f((b - space) / 360.0f, (a) / 360.0f);

					Maths::Vector3f v2 = Maths::Vector3f((float)(radius * sin(ToRadians(a - space)) * sin(ToRadians(b))), (float)(radius * cos(ToRadians(a - space)) * sin(ToRadians(b))), (float)(radius * cos(ToRadians(b))));
					Maths::Vector2f tex2 = Maths::Vector2f((b) / 360.0f, (a - space) / 360.0f);

					Maths::Vector3f v3 = Maths::Vector3f((float)(radius * sin(ToRadians(a - space)) * sin(ToRadians(b - space))), (float)(radius * cos(ToRadians(a - space)) * sin(ToRadians(b - space))), (float)(radius * cos(ToRadians(b - space))));
					Maths::Vector2f tex3 = Maths::Vector2f((b - space) / 360.0f, (a - space) / 360.0f);

					Maths::Vector3f deltaPos1 = v1 - v0;
					Maths::Vector3f deltaPos2 = v2 - v0;
					Maths::Vector2f deltaUV1 = tex1 - tex0;
					Maths::Vector2f deltaUV2 = tex2 - tex0;
					float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
					Maths::Vector3f tangent1 = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

					deltaPos1 = v2 - v1;
					deltaPos2 = v3 - v1;
					deltaUV1 = tex2 - tex1;
					deltaUV2 = tex3 - tex1;
					r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
					Maths::Vector3f tangent2 = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

					ptr->position = v0;
					ptr->normal = v0.Normalize();
					ptr->texCoord = tex0;
					ptr->color = color;
					ptr->tangent = tangent1;
					ptr++;

					ptr->position = v1;
					ptr->normal = v1.Normalize();
					ptr->texCoord = tex1;
					ptr->color = color;
					ptr->tangent = tangent1;
					ptr++;

					ptr->position = v2;
					ptr->normal = v2.Normalize();
					ptr->texCoord = tex2;
					ptr->color = color;
					ptr->tangent = tangent2;
					ptr++;

					ptr->position = v3;
					ptr->normal = v3.Normalize();
					ptr->texCoord = tex3;
					ptr->color = color;
					ptr->tangent = tangent2;
					ptr++;

					*indices = 0 + currentVertex;
					indices++;
					*indices = 1 + currentVertex;
					indices++;
					*indices = 2 + currentVertex;
					indices++;
					*indices = 3 + currentVertex;
					indices++;

					currentVertex += 4;
				}
			}
			vbo->Unmap();
			indexBuffer->Unmap();
			vao->SetRenderMode(RenderMode::TriangleStrip);
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
					ptr->position = Maths::Vector3f(-width / 2.0f + j * (width / (float)(xVertices - 1)), 0, -depth / 2.0f + i * (depth / (float)(zVertices - 1)));
					ptr->normal = Maths::Vector3f(0.0f, 1.0f, 0.0f);
					ptr->texCoord = Maths::Vector2f((float)j / (xVertices - 1), 1.0f - (float)i / (zVertices - 1));
					ptr->color = color;
					ptr->tangent = Maths::Vector3f(0.0, 0.0, -1.0);
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