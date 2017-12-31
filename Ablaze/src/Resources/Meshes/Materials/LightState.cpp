#include "LightState.h"

namespace Ablaze
{

	LightState::LightState(float specular, float shineDamper, const Color& color)
		: Shininess(specular), ShineDamper(shineDamper), SpecularHighlight(color)
	{
	
	}

	void LightState::Apply(Shader* shader) const
	{
		shader->Bind();
		shader->SetUniform("material.Shininess", Shininess);
		shader->SetUniform("material.ShineDamper", ShineDamper);
		shader->SetUniform("material.SpecularHighlight", SpecularHighlight);
	}

	void LightState::operator()(Shader* shader) const
	{
		Apply(shader);
	}

	bool LightState::operator==(const LightState& other) const
	{
		return (Shininess == other.Shininess && ShineDamper == other.ShineDamper && SpecularHighlight == other.SpecularHighlight);
	}

	bool LightState::operator!=(const LightState& other) const
	{
		return !(*this == other);
	}

}