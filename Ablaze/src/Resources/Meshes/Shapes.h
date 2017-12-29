#pragma once
#include "Common.h"
#include "Model.h"

namespace Ablaze
{
	namespace Internal
	{

		class AB_API Shapes
		{
		public:
			static VertexArray* Rectangle(float width, float height, const Color& color = Color::White());
			static VertexArray* Ellipse(float width, float height, int vertexCount, const Color& color = Color::White());
			
			static VertexArray* Cuboid(float width, float height, float depth, const Color& color = Color::White());
			static VertexArray* Sphere(float radius, int vertexSpacing, const Color& color = Color::White());
			static VertexArray* Grid(float width, float depth, int xVertices, int zVertices, const Color& color = Color::White());

		};

	}
}