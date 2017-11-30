#pragma once
#include "Common.h"
#include "Asset.h"
#include "Meshes\Model.h"
#include "Meshes\Shapes.h"
#include "Textures\__Textures__.h"
#include "Resource.h"

namespace Ablaze
{

	struct AB_API AssetPtr
	{
		Asset* ptr;
		int ref;
	};

	struct AB_API ResourceInfo
	{
	public:
		AssetLoadInfo info;

	};

	template<typename> class Resource;
	class Shader;

	// Manages all resources within Engine
	class AB_API ResourceManager : public Singleton<ResourceManager>
	{
	private:
		std::shared_ptr<Shader> m_DefaultColor;
		std::shared_ptr<Shader> m_DefaultTexture;
		std::shared_ptr<Shader> m_LightColor;
		std::shared_ptr<Shader> m_LightTexture;

	private:
		ResourceManager();

	public:
		static void Terminate();

	public:
		std::shared_ptr<Shader> LoadShader(const String& shaderFile);
		std::shared_ptr<Shader> LoadShader(const String& vFile, const String& fFile);
		std::shared_ptr<Shader> CreateShader(const String& vSource, const String& fSource);
		std::shared_ptr<Shader> CreateShader(const String& vSource, const String& gSource, const String& fSource);
		std::shared_ptr<Shader> DefaultColorShader();
		std::shared_ptr<Shader> DefaultTextureShader();
		std::shared_ptr<Shader> LightingColorShader();
		std::shared_ptr<Shader> LightingTextureShader();

		std::shared_ptr<Texture2D> LoadTexture2D(const String& textureFile, MipmapMode mipmap = MipmapMode::Enabled);
		std::shared_ptr<Texture2D> CreateBlankTexture2D(int width, int height, MipmapMode mipmap = MipmapMode::Enabled);

		std::shared_ptr<Model> LoadModel(const String& objModelFile);
		std::shared_ptr<Model> CreateRectangle(const Color& color = Color::White());
		std::shared_ptr<Model> CreateCircle(const Color& color = Color::White());
		std::shared_ptr<Model> CreateCuboid(const Color& color = Color::White());
		std::shared_ptr<Model> CreateSphere(const Color& color = Color::White());
		std::shared_ptr<Model> CreateGrid(int xVerts, int zVerts, const Color& color = Color::White());
		std::shared_ptr<Model> CreatePlane(const Color& color = Color::White());

		friend class Singleton<ResourceManager>;

	private:
		void LoadDefaultColor();
		void LoadDefaultTexture();
		void LoadLightColor();
		void LoadLightTexture();

	};

}