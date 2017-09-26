#include "ResourceManager.h"

namespace Ablaze
{

	ResourceManager* ResourceManager::s_Instance = nullptr;

	ResourceManager::ResourceManager() : Object()
	{
	
	}

	ResourceManager* ResourceManager::Get()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new ResourceManager();
		}
		return s_Instance;
	}

	Shader* ResourceManager::CreateShader(const String& vFile, const String& fFile)
	{
		return Shader::FromFile(vFile, fFile);
	}

	Texture2D* ResourceManager::CreateTexture2D(const String& file, MipmapMode mm)
	{
		return new Texture2D(file, mm);
	}

	String ResourceManager::ToString() const
	{
		return "ResourceManager";
	}

}