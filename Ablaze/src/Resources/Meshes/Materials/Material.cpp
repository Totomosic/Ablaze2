#include "Material.h"

namespace Ablaze
{

	Material::Material(const String& filename) : Asset(filename)
	{
		// Load from file
	}

	Material::Material(const Color& baseColor, const RenderState& renderState, const Texture2DSet& textures) : Asset(),
		m_BaseColor(baseColor), m_RenderState(renderState), m_Textures(textures)
	{
	
	}

	Material::Material(const Color& baseColor, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture) : Material(baseColor, renderState, Texture2DSet(samplerName, texture))
	{
		
	}

	Material::Material(const Color& baseColor, const RenderState& renderState) : Material(baseColor, renderState, Texture2DSet())
	{
	
	}

	Material::Material(const Color& baseColor, const Texture2DSet& textures) : Material(baseColor, RenderState(), textures)
	{
	
	}

	Material::Material(const Color& baseColor, const String& samplerName, const Resource<Texture2D>& texture) : Material(baseColor, Texture2DSet(samplerName, texture))
	{
	
	}

	Material::Material(const Color& baseColor) : Material(baseColor, RenderState())
	{
	
	}

	Material::Material(const RenderState& renderState, const Texture2DSet& textures) : Material(Color::White(), renderState, textures)
	{
	
	}

	Material::Material(const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture) : Material(renderState, Texture2DSet(samplerName, texture))
	{
	
	}

	Material::Material(const RenderState& renderState) : Material(renderState, Texture2DSet())
	{
	
	}

	Material::Material(const Texture2DSet& textures) : Material(RenderState(), textures)
	{
	
	}

	Material::Material(const String& samplerName, const Resource<Texture2D>& texture) : Material(Texture2DSet(samplerName, texture))
	{
	
	}

	Material::Material() : Material(Color::White())
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

	void Material::Reload()
	{
	
	}

	String Material::ToString() const
	{
		return "Material";
	}

}