#include "Texture2DSet.h"
#include "Resources\Resource.h"
#include "Resources\ResourceManager.h"

namespace Ablaze
{

	Texture2DSet::Texture2DSet() : Object(),
		m_Textures(), m_Lookup()
	{
	
	}

	Texture2DSet::Texture2DSet(const String& samplerName, const Resource<Texture2D>& texture) : Object(),
		m_Textures(), m_Lookup()
	{
		AddTexture(samplerName, texture);
	}

	Texture2DSet::Texture2DSet(const String& samplerName, const String& textureFile) : Texture2DSet(samplerName, ResourceManager::Library().LoadTexture2D(textureFile))
	{
		
	}

	const String& Texture2DSet::GetSampler(int index) const
	{
		return m_Lookup.at(index);
	}

	const Resource<Texture2D>& Texture2DSet::GetTexture(int index) const
	{
		return m_Textures[index];
	}

	int Texture2DSet::GetTextureCount() const
	{
		return m_Textures.size();
    }

	void Texture2DSet::AddTexture(const String& samplerName, const Resource<Texture2D>& texture)
	{
		int index = m_Textures.size();
		m_Textures.push_back(texture);
		m_Lookup[index] = samplerName;
	}

	void Texture2DSet::AddTexture(const String& samplerName, const String& textureFile)
	{
		AddTexture(samplerName, ResourceManager::Library().LoadTexture2D(textureFile));
	}

	void Texture2DSet::RemoveTexture(int index)
	{
		m_Textures.erase(m_Textures.begin() + index);
		m_Lookup.erase(index);
	}

	void Texture2DSet::Clear()
	{
		m_Textures.clear();
	}

	void Texture2DSet::BindAll(const Resource<Shader>& shader) const
	{
		for (int i = 0; i < GetTextureCount(); i++)
		{
			shader->SetTexture(m_Lookup.at(i), m_Textures[i]);
		}
	}

	String Texture2DSet::ToString() const
	{
		return "Texture2DSet";
	}

}