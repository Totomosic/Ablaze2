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
			shader->SetTexture(m_Lookup.at(i), m_Textures[i]);
		}
	}

	String TextureSet::ToString() const
	{
		return "TextureSet";
	}

	void TextureSet::Serialize(JSONwriter& writer) const
	{

	}


}