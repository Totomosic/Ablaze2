#pragma once
#include "Common.h"
#include "Resources\Shaders\Shader.h"

namespace Ablaze
{

	struct AB_API LightState
	{
	public:
		float Shininess;
		float ShineDamper;
		Color SpecularHighlight;

	public:
		LightState(float shininess = 0.0f, float shineDamper = 1.0f, const Color& color = Color::White());

		void Apply(Shader* shader) const;
		void operator()(Shader* shader) const;

	};

}