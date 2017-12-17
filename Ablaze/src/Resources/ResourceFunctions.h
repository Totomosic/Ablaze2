#pragma once
#include "ResourceManager.h"

namespace Ablaze
{

	Texture2D* SetTexture2D(const String& name, Texture2D* texture);
	Model* SetModel(const String& name, Model* model);
	Font* SetFont(const String& name, Font* font);
	Shader* SetShader(const String& name, Shader* shader);
	Texture2D* GetTexture2D(const String& name);
	Model* GetModel(const String& name);
	Font* GetFont(const String& name);
	Shader* GetShader(const String& name);

}