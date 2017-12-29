#include "Material.h"

namespace Ablaze
{

	Material::Material(const Color& color, Shader* shader, const RenderState& renderState) : Asset(),
		m_BaseColor(color), m_Shader(shader), m_RenderState(renderState), m_Textures()
	{
		shader->Increment();
	}

	Material::Material(const Color& color, Shader* shader, const String& sampler, Texture* texture) : Material(color, shader, RenderState())
	{
		m_Textures.AddTexture(sampler, texture);
	}

	Material::Material(const Color& color, Shader* shader) : Material(color, shader, RenderState())
	{

	}

	Material::~Material()
	{
		m_Shader->Decrement();
	}

	const Color& Material::BaseColor() const
	{
		return m_BaseColor;
	}

	Color& Material::BaseColor()
	{
		return m_BaseColor;
	}

	const RenderState& Material::RenderSettings() const
	{
		return m_RenderState;
	}

	RenderState& Material::RenderSettings()
	{
		return m_RenderState;
	}

	const LightState& Material::LightSettings() const
	{
		return m_LightState;
	}

	LightState& Material::LightSettings()
	{
		return m_LightState;
	}

	Shader* Material::ActiveShader() const
	{
		return m_Shader;
	}

	const UniformManager& Material::Uniforms() const
	{
		return m_Uniforms;
	}

	UniformManager& Material::Uniforms()
	{
		return m_Uniforms;
	}

	const TextureSet& Material::Textures() const 
	{ 
		return m_Textures; 
	}

	TextureSet& Material::Textures() 
	{ 
		return m_Textures;
	}

	void Material::Apply() const
	{
		m_Shader->Bind();
		m_RenderState.Apply();
		m_LightState.Apply(m_Shader);
		m_Uniforms.UploadAll(m_Shader);
		m_Textures.BindAll(m_Shader);
		m_Shader->Unbind();
	}

	void Material::Reload()
	{
	
	}

	String Material::ToString() const
	{
		return "Material";
	}

	void Material::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.EndObject();
	}

}