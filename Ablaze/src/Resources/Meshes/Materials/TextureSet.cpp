#include "TextureSet.h"

namespace Ablaze
{

	TextureSet::TextureSet() : Object(),
		m_Textures(), m_Lookup()
	{

	}

	TextureSet::TextureSet(const String& sampler, Texture* texture) : TextureSet()
	{
		AddTexture(sampler, texture);
	}

	TextureSet::TextureSet(const TextureSet& other)
	{
		for (int i = 0; i < other.m_Textures.size(); i++)
		{
			AddTexture(other.m_Lookup.at(i), other.m_Textures[i]);
		}
	}

	TextureSet& TextureSet::operator=(const TextureSet& other)
	{
		for (int i = m_Textures.size() - 1; i >= 0; i--)
		{
			Texture* texture = m_Textures[i];
			texture->Decrement();
			m_Textures.erase(m_Textures.begin() + i);
		}
		m_Lookup.clear();
		for (int i = 0; i < other.m_Textures.size(); i++)
		{
			AddTexture(other.m_Lookup.at(i), other.m_Textures[i]);
		}
		return *this;
	}

	TextureSet::~TextureSet()
	{
		for (Texture* tex : m_Textures)
		{
			tex->Decrement();
		}
	}

	const String& TextureSet::GetSampler(int index) const
	{
		return m_Lookup.at(index);
	}

	Texture* TextureSet::GetTexture(int index) const
	{
		return m_Textures[index];
	}

	int TextureSet::TextureCount() const
	{
		return m_Textures.size();
	}

	void TextureSet::AddTexture(const String& sampler, Texture* texture)
	{
		texture->Increment();
		int index = m_Textures.size();
		m_Textures.push_back(texture);
		m_Lookup[index] = sampler;
	}

	void TextureSet::RemoveTexture(int index)
	{
		m_Textures.erase(m_Textures.begin() + index);
	}

	void TextureSet::BindAll(Shader* shader) const
	{
		for (int i = 0; i < TextureCount(); i++)
		{
			shader->SetTexture(m_Lookup.at(i), m_Textures[i], i);
		}
	}

	bool TextureSet::operator==(const TextureSet& other) const
	{
		if (other.m_Textures.size() != m_Textures.size())
		{
			return false;
		}
		for (int i = 0; i < m_Textures.size(); i++)
		{
			if (m_Textures[i] != other.m_Textures[i])
			{
				return false;
			}
		}
		return true;
	}

	bool TextureSet::operator!=(const TextureSet& other) const
	{
		return !(*this == other);
	}

	String TextureSet::ToString() const
	{
		return "TextureSet";
	}

	void TextureSet::Serialize(JSONwriter& writer) const
	{

	}


}