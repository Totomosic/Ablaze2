#pragma once
#include "Common.h"
#include "LightState.h"
#include "RenderState.h"
#include "TextureSet.h"

namespace Ablaze
{

	class AB_API Material : public Asset
	{
	private:
		Color m_BaseColor;
		Shader* m_Shader;
		UniformManager m_Uniforms;
		LightState m_LightState;
		RenderState m_RenderState;
		TextureSet m_Textures;

	public:
		Material(const Color& color, Shader* shader, const RenderState& renderState);
		Material(const Color& color, Shader* shader, const String& sampler, Texture* texture);
		Material(const Color& color, Shader* shader);
		~Material();

		const Color& BaseColor() const;
		Color& BaseColor();
		const RenderState& RenderSettings() const;
		RenderState& RenderSettings();
		const LightState& LightSettings() const;
		LightState& LightSettings();
		Shader* ActiveShader() const;
		const UniformManager& Uniforms() const;
		UniformManager& Uniforms();
		const TextureSet& Textures() const;
		TextureSet& Textures();

		void Reload() override;
		void Apply() const;

		String ToString() const;
		void Serialize(JSONwriter& writer) const;

	};

}