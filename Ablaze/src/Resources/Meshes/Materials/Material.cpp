#include "Material.h"

namespace Ablaze
{

	Material::Material(const Color& baseColor, const Resource<Shader>& shader, const RenderState& renderState, const Texture2DSet& textures) : Asset(),
		m_BaseColor(baseColor), m_RenderState(renderState), m_Textures(textures), m_Shader(shader)
	{
	
	}

	Material::Material(const Color& baseColor, const Resource<Shader>& shader, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture) : Material(baseColor, shader, renderState, Texture2DSet(samplerName, texture))
	{
		
	}

	Material::Material(const Color& baseColor, const Resource<Shader>& shader, const RenderState& renderState, const String& samplerName, const String& textureFile) : Material(baseColor, shader, renderState, Texture2DSet(samplerName, textureFile))
	{

	}

	Material::Material(const Color& baseColor, const Resource<Shader>& shader, const RenderState& renderState) : Material(baseColor, shader, renderState, Texture2DSet())
	{
	
	}

	Material::Material(const Color& baseColor, const Resource<Shader>& shader, const Texture2DSet& textures) : Material(baseColor, shader, RenderState(), textures)
	{
	
	}

	Material::Material(const Color& baseColor, const Resource<Shader>& shader, const String& samplerName, const Resource<Texture2D>& texture) : Material(baseColor, shader, Texture2DSet(samplerName, texture))
	{
	
	}

	Material::Material(const Color& baseColor, const Resource<Shader>& shader, const String& samplerName, const String& textureFile) : Material(baseColor, shader, Texture2DSet(samplerName, textureFile))
	{

	}

	Material::Material(const Color& baseColor, const Resource<Shader>& shader) : Material(baseColor, shader, RenderState())
	{
	
	}

	Material::Material(const Resource<Shader>& shader, const RenderState& renderState, const Texture2DSet& textures) : Material(Color::White(), shader, renderState, textures)
	{
	
	}

	Material::Material(const Resource<Shader>& shader, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture) : Material(shader, renderState, Texture2DSet(samplerName, texture))
	{
	
	}

	Material::Material(const Resource<Shader>& shader, const RenderState& renderState, const String& samplerName, const String& textureFile) : Material(shader, renderState, Texture2DSet(samplerName, textureFile))
	{

	}

	Material::Material(const Resource<Shader>& shader, const RenderState& renderState) : Material(shader, renderState, Texture2DSet())
	{
	
	}

	Material::Material(const Resource<Shader>& shader, const Texture2DSet& textures) : Material(shader, RenderState(), textures)
	{
	
	}

	Material::Material(const Resource<Shader>& shader, const String& samplerName, const Resource<Texture2D>& texture) : Material(shader, Texture2DSet(samplerName, texture))
	{
	
	}

	Material::Material(const Resource<Shader>& shader, const String& samplerName, const String& textureFile) : Material(shader, Texture2DSet(samplerName, textureFile))
	{

	}

	Material::Material(const Resource<Shader>& shader) : Material(Color::White(), shader)
	{
	
	}

	Material::Material(const Color& baseColor, const String& shaderFile, const RenderState& renderState, const Texture2DSet& textures) : Material(baseColor, ResourceManager::Library().LoadShader(shaderFile), renderState, textures)
	{

	}

	Material::Material(const Color& baseColor, const String& shaderFile, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture) : Material(baseColor, ResourceManager::Library().LoadShader(shaderFile), renderState, samplerName, texture)
	{

	}

	Material::Material(const Color& baseColor, const String& shaderFile, const RenderState& renderState, const String& samplerName, const String& textureFile) : Material(baseColor, ResourceManager::Library().LoadShader(shaderFile), renderState, samplerName, textureFile)
	{

	}

	Material::Material(const Color& baseColor, const String& shaderFile, const RenderState& renderState) : Material(baseColor, ResourceManager::Library().LoadShader(shaderFile), renderState)
	{

	}

	Material::Material(const Color& baseColor, const String& shaderFile, const Texture2DSet& textures) : Material(baseColor, ResourceManager::Library().LoadShader(shaderFile), textures)
	{

	}

	Material::Material(const Color& baseColor, const String& shaderFile, const String& samplerName, const Resource<Texture2D>& texture) : Material(baseColor, ResourceManager::Library().LoadShader(shaderFile), samplerName, texture)
	{

	}

	Material::Material(const Color& baseColor, const String& shaderFile, const String& samplerName, const String& textureFile) : Material(baseColor, ResourceManager::Library().LoadShader(shaderFile), samplerName, textureFile)
	{

	}

	Material::Material(const Color& baseColor, const String& shaderFile) : Material(baseColor, ResourceManager::Library().LoadShader(shaderFile))
	{

	}

	Material::Material(const String& shaderFile, const RenderState& renderState, const Texture2DSet& textures) : Material(ResourceManager::Library().LoadShader(shaderFile), renderState, textures)
	{

	}

	Material::Material(const String& shaderFile, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture) : Material(ResourceManager::Library().LoadShader(shaderFile), samplerName, texture)
	{

	}

	Material::Material(const String& shaderFile, const RenderState& renderState, const String& samplerName, const String& textureFile) : Material(ResourceManager::Library().LoadShader(shaderFile), renderState, samplerName, textureFile)
	{

	}

	Material::Material(const String& shaderFile, const RenderState& renderState) : Material(ResourceManager::Library().LoadShader(shaderFile), renderState)
	{

	}

	Material::Material(const String& shaderFile, const Texture2DSet& textures) : Material(ResourceManager::Library().LoadShader(shaderFile), textures)
	{

	}

	Material::Material(const String& shaderFile, const String& samplerName, const Resource<Texture2D>& texture) : Material(ResourceManager::Library().LoadShader(shaderFile), samplerName, texture)
	{

	}

	Material::Material(const String& shaderFile, const String& samplerName, const String& textureFile) : Material(ResourceManager::Library().LoadShader(shaderFile), samplerName, textureFile)
	{

	}

	Material::Material(const String& shaderFile) : Material(ResourceManager::Library().LoadShader(shaderFile))
	{

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

	const Texture2DSet& Material::Textures() const
	{
		return m_Textures;
	}

	Texture2DSet& Material::Textures()
	{
		return m_Textures;
	}

	const Resource<Shader>& Material::GetShader() const
	{
		return m_Shader;
	}

	Resource<Shader>& Material::GetShader()
	{
		return m_Shader;
	}

	void Material::Reload()
	{
	
	}

	String Material::ToString() const
	{
		return "Material";
	}

}