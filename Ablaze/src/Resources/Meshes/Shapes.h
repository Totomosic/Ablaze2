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
			//static Model* Circle(float r, const Color& color = Color::White(), int divisions = 10);

		};

	}
}