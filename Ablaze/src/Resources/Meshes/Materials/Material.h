#pragma once
#include "MaterialBase.h"
#include "TextureSet.h"
#include "Resources\ResourceManager.h"

namespace Ablaze
{

	template<typename T>
	class AB_API Material : public MaterialBase
	{
	private:
		TextureSet<T> m_Textures;

	public:
		Material(const Color& color, const Resource<Shader>& shader, const TextureSet<T>& textures, const RenderState& renderState) : MaterialBase(color, shader, renderState),
			m_Textures(textures)
		{
			
		}

		Material(const Color& color, const Resource<Shader>& shader, const RenderState& renderState) : Material(color, shader, TextureSet<T>(), renderState)
		{
		
		}

		Material(const Color& color, const Resource<Shader>& shader, const String& sampler, const Resource<T>& texture) : Material(color, shader, RenderState())
		{
			m_Textures.AddTexture(sampler, texture);
		}

		Material(const Color& color, const Resource<Shader>& shader, const String& sampler, const String& textureFilename) : Material(color, shader, RenderState())
		{
			m_Textures.AddTexture(sampler, ResourceManager::Library().Load<T>(textureFilename));
		}

		Material(const Color& color, const Resource<Shader>& shader) : Material(color, shader, RenderState())
		{
		
		}

		const TextureSet<T>& Textures() const { return m_Textures; }
		TextureSet<T>& Textures() { return m_Textures; }

		void Apply() const override
		{
			m_Shader->Bind();
			m_RenderState.Apply();
			m_Textures.BindAll(m_Shader);
			m_Shader->Unbind();
		}

		String ToString() const
		{
			return "Material";
		}

		MaterialBase* Clone() const override
		{
			Material<T>* mat = new Material<T>(BaseColor(), ActiveShader(), RenderSettings());
			mat->Textures() = Textures();
			return mat;
		}

	};

}