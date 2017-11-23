#pragma once
#include "Common.h"
#include "Asset.h"
#include "Meshes\Model.h"
#include "Meshes\Shapes.h"
#include "Shaders\ShaderProgram.h"
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
	class AB_API ResourceManager : public Object
	{
	private:
		std::unordered_map<AssetLoadInfo, AssetPtr> m_Assets;

	private:
		ResourceManager();

	public:
		static ResourceManager& Library();

	public:
		template<typename T>
		Resource<T> Load(const String& filename)
		{
			if (typeid(T) == typeid(Texture2D))
			{
				return (Resource<T>)LoadTexture2D(filename);
			}
			else if (typeid(T) == typeid(Model))
			{
				return (Resource<T>)LoadOBJModel(filename);
			}
			else if (typeid(T) == typeid(Font))
			{
				return (Resource<T>)LoadFont(filename, 16);
			}
			AB_ERROR("Unable to load type");
			return Resource<T>(nullptr);
		}

		Resource<Texture2D> LoadTexture2D(const String& filename, MipmapMode mipmap = MipmapMode::Enabled);
		Resource<Font> LoadFont(const String& filename, float size);

		Resource<ShaderProgram> LoadShaderProgram(ShaderType type, const String& filename);
		Resource<Shader> LoadShader(const String& vFile, const String& fFile);
		Resource<Shader> LoadShader(const String& shaderFile);
		Resource<Shader> DefaultColorShader();
		Resource<Shader> DefaultTextureShader();
		Resource<Shader> LightingColorShader();
		Resource<Shader> LightingTextureShader();
		Resource<Shader> DefaultWireframeShader();

		Resource<Model> LoadOBJModel(const String& objFile);

		Resource<Texture2D> CreateBlankTexture2D(uint width, uint height, MipmapMode mipmap = MipmapMode::Disabled);
		Resource<ShaderProgram> CreateShaderProgram(ShaderType type, const String& shaderSource);

		Resource<Model> CreateRectangle(float width, float height, const Color& color = Color::White());
		Resource<Model> CreateCircle(float radius, const Color& color = Color::White());
		Resource<Model> CreateEllipse(float width, float height, const Color& color = Color::White());
		
		Resource<Model> CreateCuboid(float width, float height, float depth, const Color& color = Color::White());
		Resource<Model> CreateSphere(float radius, const Color& color = Color::White());
		Resource<Model> CreatePlane(float width, float depth, const Color& color = Color::White());
		Resource<Model> CreateGrid(float width, float height, int xVertices, int zVertices, const Color& color = Color::White()); // x and yVertices must be >= 2

		String ToString() const override;

		template<typename> friend class Resource;

	private:
		void AddNewAsset(const AssetLoadInfo& info, Asset* asset, int initalRefCount = 1);
		void DecrementRefCount(const AssetLoadInfo& info, int count = 1);
		void IncrementRefCount(const AssetLoadInfo& info, int count = 1);
		void DeleteAsset(const AssetLoadInfo& info);
		AssetPtr& GetAsset(const AssetLoadInfo& info);
		bool AssetExists(const AssetLoadInfo& info);

		Texture2D* CreateNewTexture2D(const String& filename, MipmapMode mipmap);
		Font* CreateNewFont(const String& filename, float size);
		Shader* CreateNewShader(const String& vFile, const String& fFile);
		Shader* CreateNewShader(const String& shaderFile);
		ShaderProgram* CreateNewShaderProgram(ShaderType type, const String& fileOrSource, bool isFile);
		Model* CreateNewOBJModel(const String& filename);


	};

}