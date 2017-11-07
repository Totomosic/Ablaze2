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
			static Model* Rectangle(float width, float height, const Color& color = Color::White());
			static Model* Ellipse(float width, float height, int vertexCount, const Color& color = Color::White());
			
			static Model* Cuboid(float width, float height, float depth, const Color& color = Color::White());
			static Model* Sphere(float radius, int vertexSpacing, const Color& color = Color::White());
			static Model* Grid(float width, float depth, int xVertices, int zVertices, const Color& color = Color::White());

		};

	}
}