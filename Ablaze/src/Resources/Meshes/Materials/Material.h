#pragma once
#include "Common.h"
#include "LightState.h"
#include "RenderState.h"
#include "TextureSet.h"

namespace Ablaze
{

	class AB_API Material : public Object
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
		Material();
		Material(const Material& other);
		~Material();

		Material& operator=(const Material& other);

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

		void Apply() const;

		bool operator==(const Material& other) const;
		bool operator!=(const Material& other) const;

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;

	};

}