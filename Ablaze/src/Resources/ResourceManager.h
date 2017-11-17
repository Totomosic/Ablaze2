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

	struct AB_API ResourceInfo
	{
	public:
		AssetType type;
		String resourceName;
		int resourceID;

	};

	template<typename> class Resource;
	class Shader;

	// Manages all resources within Engine
	class AB_API ResourceManager : public Object
	{
	private:
		int m_MaxGenResources;
		std::unordered_map<String, std::pair<int, Asset*>> m_LoadedResources;
		std::pair<int, Asset*>** m_GeneratedResources;
		int m_GeneratedResourceCount;
		
		std::unordered_map<String, ResourceInfo> m_SavedResources;

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
				Resource<Texture2D> res = LoadTexture2D(filename);
				Texture2D* texture = (Texture2D*)m_LoadedResources[filename].second;
				IncrementLoadedRefCount(filename);
				return Resource<T>((T*)texture);
			}
			else if (typeid(T) == typeid(Model))
			{
				Resource<Model> res = LoadOBJModel(filename);
				Model* model = (Model*)m_LoadedResources[filename].second;
				IncrementLoadedRefCount(filename);
				return Resource<T>((T*)model);
			}
			else if (typeid(T) == typeid(Font))
			{
				Resource<Font> res = LoadFont(filename, 16);
				Font* font = (Font*)m_LoadedResources[filename].second;
				IncrementLoadedRefCount(filename);
				return Resource<T>((T*)font);
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

		template<typename T>
		void SaveResource(const String& name, const Resource<T>& resource)
		{
			m_SavedResources[name] = { resource->GetAssetType(), resource->Filename(), resource->ResourceID() };
			IncrementRefCount(resource);
		}

		template<typename T>
		Resource<T> OpenResource(const String& name)
		{
			if (m_SavedResources[name].type == AssetType::Loaded)
			{
				std::pair<int, Asset*>& pair = m_LoadedResources[m_SavedResources[name].resourceName];
				IncrementLoadedRefCount(m_SavedResources[name].resourceName);
				return Resource<T>((T*)pair.second);
			}
			else
			{
				std::pair<int, Asset*>& pair = *m_GeneratedResources[m_SavedResources[name].resourceID];
				IncrementGeneratedRefCount(m_SavedResources[name].resourceID);
				return Resource<T>((T*)pair.second);
			}
		}

		int GetLoadedRefCount(const String& assetName);
		int GetGeneratedRefCount(int resourceID);

		template<typename T>
		int GetRefCount(const Resource<T>& resource)
		{
			if (resource->GetAssetType() == AssetType::Loaded)
			{
				return GetLoadedRefCount(resource->Filename());
			}
			return GetGeneratedRefCount(resource->ResourceID());
		}

		String ToString() const override;

		template<typename> friend class Resource;

	private:
		template<typename T>
		void IncrementRefCount(const Resource<T>& resource)
		{
			if (resource->GetAssetType() == AssetType::Loaded)
			{
				if (LoadedResourceExists(resource->Filename()))
				{
					IncrementLoadedRefCount(resource->Filename());
				}
				return;
			}
			if (GeneratedResourceExists(resource->ResourceID()))
			{
				IncrementGeneratedRefCount(resource->ResourceID());
			}
		}

		template<typename T>
		void DecrementRefCount(const Resource<T>& resource)
		{
			if (resource->GetAssetType() == AssetType::Loaded)
			{
				if (LoadedResourceExists(resource->Filename()))
				{
					DecrementLoadedRefCount(resource->Filename());
				}
				return;
			}
			if (GeneratedResourceExists(resource->ResourceID()))
			{
				DecrementGeneratedRefCount(resource->ResourceID());
			}
		}

		bool LoadedResourceExists(const String& assetName);
		void IncrementLoadedRefCount(const String& assetName);
		void DecrementLoadedRefCount(const String& assetName);
		void DeleteLoadedResource(const String& assetName);
		std::pair<int, Asset*>& GetLoadedResource(const String& assetName);
		void CreateNewLoadedResource(const String& assetName, Asset* asset);
		void TestLoadedRefCount(int refCount, const String& assetName);
		Asset* GetLoadedResourcePtr(const String& assetName);

		bool GeneratedResourceExists(int resourceID);
		void CreateNewGeneratedResource(Asset* asset);
		void IncrementGeneratedRefCount(int resourceID);
		void DecrementGeneratedRefCount(int resourceID);
		void DeleteGeneratedResource(int resourceID);
		std::pair<int, Asset*>& GetGeneratedResource(int resourceID);
		void TestGeneratedRefCount(int refCount, int resourceID);
		Asset* GetGeneratedResourcePtr(int resourceID);

		void DeleteAssetPtr(Asset* ptr);

		Texture2D* CreateNewTexture2D(const String& filename, MipmapMode mipmap);
		Font* CreateNewFont(const String& filename, float size);
		Shader* CreateNewShader(const String& vFile, const String& fFile);
		Shader* CreateNewShader(const String& shaderFile);
		ShaderProgram* CreateNewShaderProgram(ShaderType type, const String& fileOrSource, bool isFile);
		Model* CreateNewOBJModel(const String& filename);


	};

}