#pragma once
#include "Common.h"
#include "Meshes\__Meshes__.h"
#include "Shaders\__Shaders__.h"
#include "Textures\__Textures__.h"

namespace Ablaze
{

	class ResourceManager : public Object
	{
	private:
		static ResourceManager* s_Instance;

	private:

	private:
		ResourceManager();

	public:
		static ResourceManager* Get();

	public:
		Shader* CreateShader(const String& vFile, const String& fFile);
		Texture2D* CreateTexture2D(const String& file, MipmapMode mm = MipmapMode::Enabled);

		String ToString() const override;

	};

}