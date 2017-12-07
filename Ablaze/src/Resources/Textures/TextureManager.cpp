#include "TextureManager.h"

namespace Ablaze
{

	TextureManager::TextureManager()
	{
		GL_CALL(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_MaxBindPorts));
		m_TextureArray = new const Texture*[m_MaxBindPorts];
		Initialise();
	}

	void TextureManager::Bind(const Texture* const texture)
	{
		if (texture->m_BindPort == -1)
		{
			BindNewTexture(texture);
		}
		else
		{
			GL_CALL(glActiveTexture(GL_TEXTURE0 + texture->m_BindPort));
			GL_CALL(glBindTexture((GLenum)texture->GetTarget(), texture->GetID()));
		}
	}

	void TextureManager::Unbind(const Texture* const texture)
	{
	
	}

	void TextureManager::BindNewTexture(const Texture* const texture)
	{
		int unit = GetNextAvailableUnit();
		texture->m_BindPort = unit;
		GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
		GL_CALL(glBindTexture((GLenum)texture->GetTarget(), texture->GetID()));
		m_TextureArray[unit] = texture;
	}

	void TextureManager::Initialise()
	{
		for (int i = 0; i < m_MaxBindPorts; i++)
		{
			m_TextureArray[i] = nullptr;
		}
	}

	int TextureManager::GetNextAvailableUnit()
	{
		for (int i = 0; i < m_MaxBindPorts; i++)
		{
			if (m_TextureArray[i] == nullptr)
			{
				return i;
			}
		}
		return -1;
	}

	void TextureManager::Delete(int bindport)
	{
		m_TextureArray[bindport] = nullptr;
	}

}