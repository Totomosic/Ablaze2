#include "ResourceFunctions.h"

namespace Ablaze
{

	Texture2D* SetTexture2D(const String & name, Texture2D* texture)
	{
		return ResourceManager::SetTexture2D(name, texture);
	}

	Model* SetModel(const String & name, Model* model)
	{
		return ResourceManager::SetModel(name, model);
	}

	Font* SetFont(const String & name, Font* font)
	{
		return ResourceManager::SetFont(name, font);
	}

	Shader* SetShader(const String & name, Shader* shader)
	{
		return ResourceManager::SetShader(name, shader);
	}

	Texture2D* GetTexture2D(const String & name)
	{
		return ResourceManager::GetTexture2D(name);
	}

	Model* GetModel(const String & name)
	{
		return ResourceManager::GetModel(name);
	}

	Font* GetFont(const String & name)
	{
		return ResourceManager::GetFont(name);
	}

	Shader* GetShader(const String & name)
	{
		return ResourceManager::GetShader(name);
	}

}