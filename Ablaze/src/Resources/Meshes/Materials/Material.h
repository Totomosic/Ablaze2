#pragma once
#include "Common.h"
#include "Resources\Asset.h"
#include "RenderState.h"
#include "Texture2DSet.h"
#include "Resources\Shaders\Shader.h"

namespace Ablaze
{

	template<typename> class Resource;

	class AB_API Material : public Asset
	{
	private:
		Color m_BaseColor;
		RenderState m_RenderState;
		Texture2DSet m_Textures;
		Resource<Shader> m_Shader;

	public:
		// TODO: Create material File
		Material(const Color& baseColor, const Resource<Shader>& shader, const RenderState& renderState, const Texture2DSet& textures);
		Material(const Color& baseColor, const Resource<Shader>& shader, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const Color& baseColor, const Resource<Shader>& shader, const RenderState& renderState, const String& samplerName, const String& textureFile);
		Material(const Color& baseColor, const Resource<Shader>& shader, const RenderState& renderState);
		Material(const Color& baseColor, const Resource<Shader>& shader, const Texture2DSet& textures);
		Material(const Color& baseColor, const Resource<Shader>& shader, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const Color& baseColor, const Resource<Shader>& shader, const String& samplerName, const String& textureFile);
		Material(const Color& baseColor, const Resource<Shader>& shader);
		Material(const Resource<Shader>& shader, const RenderState& renderState, const Texture2DSet& textures);
		Material(const Resource<Shader>& shader, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const Resource<Shader>& shader, const RenderState& renderState, const String& samplerName, const String& textureFile);
		Material(const Resource<Shader>& shader, const RenderState& renderState);
		Material(const Resource<Shader>& shader, const Texture2DSet& textures);
		Material(const Resource<Shader>& shader, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const Resource<Shader>& shader, const String& samplerName, const String& textureFile);
		Material(const Resource<Shader>& shader);
		Material(const Color& baseColor, const String& shaderFile, const RenderState& renderState, const Texture2DSet& textures);
		Material(const Color& baseColor, const String& shaderFile, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const Color& baseColor, const String& shaderFile, const RenderState& renderState, const String& samplerName, const String& textureFile);
		Material(const Color& baseColor, const String& shaderFile, const RenderState& renderState);
		Material(const Color& baseColor, const String& shaderFile, const Texture2DSet& textures);
		Material(const Color& baseColor, const String& shaderFile, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const Color& baseColor, const String& shaderFile, const String& samplerName, const String& textureFile);
		Material(const Color& baseColor, const String& shaderFile);
		Material(const String& shaderFile, const RenderState& renderState, const Texture2DSet& textures);
		Material(const String& shaderFile, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const String& shaderFile, const RenderState& renderState, const String& samplerName, const String& textureFile);
		Material(const String& shaderFile, const RenderState& renderState);
		Material(const String& shaderFile, const Texture2DSet& textures);
		Material(const String& shaderFile, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const String& shaderFile, const String& samplerName, const String& textureFile);
		Material(const String& shaderFile);

		const Color& BaseColor() const;
		Color& BaseColor();
		const RenderState& RenderSettings() const;
		RenderState& RenderSettings();
		const Texture2DSet& Textures() const;
		Texture2DSet& Textures();
		const Resource<Shader>& GetShader() const;
		Resource<Shader>& GetShader();

		void Reload() override;

		String ToString() const override;

	};

}