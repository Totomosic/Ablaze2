#pragma once
#include "Common.h"
#include "Asset.h"
#include "Meshes\Model.h"
#include "Meshes\Shapes.h"
#include "Shaders\__Shaders__.h"
#include "Textures\__Textures__.h"

namespace Ablaze
{

	template<typename> class Resource;

	// Manages all resources within Engine
	class AB_API ResourceManager : public Object
	{
	private:
		int m_MaxGenResources;
		std::unordered_map<String, std::pair<int, Asset*>> m_LoadedResources;
		std::pair<int, Asset*>** m_GeneratedResources;
		int m_GeneratedResourceCount;

	private:
		ResourceManager();

	public:
		static ResourceManager& Library();

	public:
		Resource<Texture2D> CreateBlankTexture2D(uint width, uint height, MipmapMode mipmap = MipmapMode::Disabled);

		Resource<Texture2D> LoadTexture2D(const String& filename, MipmapMode mipmap = MipmapMode::Enabled);
		Resource<Shader> LoadShader(const String& vFile, const String& fFile);
		Resource<Shader> LoadShader(const String& shaderFile);
		Resource<Model> LoadOBJModel(const String& objFile);

		Resource<Model> CreateRectangle(float width, float height, const Color& color = Color::White());
		Resource<Model> CreateCircle(float radius, const Color& color = Color::White());
		Resource<Model> CreateEllipse(float width, float height, const Color& color = Color::White());
		
		Resource<Model> CreateCuboid(float width, float height, float depth, const Color& color = Color::White());
		Resource<Model> CreateSphere(float radius, const Color& color = Color::White());
		Resource<Model> CreatePlane(float width, float depth, const Color& color = Color::White());
		Resource<Model> CreateGrid(float width, float height, int xVertices, int zVertices, const Color& color = Color::White()); // x and yVertices must be >= 2

		template<typename T>
		int GetRefCount(const Resource<T>& resource)
		{
			if (resource->GetAssetType() == AssetType::Loaded)
			{
				return GetLoadedRefCount(resource->Filename());
			}
			else
			{
				return GetGeneratedRefCount(resource->ResourceID());
			}
		}

		String ToString() const override;

		template<typename> friend class Resource;

	private:
		template<typename T>
		void IncrementRefCount(const Resource<T>& resource)
		{
			if (resource->GetAssetType() == AssetType::Loaded)
			{
				IncrementLoadedRefCount(resource->Filename());
			}
			else
			{
				IncrementGeneratedRefCount(resource->ResourceID());
			}
		}

		template<typename T>
		void DecrementRefCount(const Resource<T>& resource)
		{
			if (resource->GetAssetType() == AssetType::Loaded)
			{
				DecrementLoadedRefCount(resource->Filename());
			}
			else
			{
				DecrementGeneratedRefCount(resource->ResourceID());
			}
		}

		bool LoadedResourceExists(const String& assetName);
		int GetLoadedRefCount(const String& assetName);
		void IncrementLoadedRefCount(const String& assetName);
		void DecrementLoadedRefCount(const String& assetName);
		void DeleteLoadedResource(const String& assetName);
		std::pair<int, Asset*>& GetLoadedResource(const String& assetName);
		void CreateNewLoadedResource(const String& assetName, Asset* asset);
		void TestLoadedRefCount(int refCount, const String& assetName);
		Asset* GetLoadedResourcePtr(const String& assetName);

		bool GeneratedResourceExists(int resourceID);
		void CreateNewGeneratedResource(Asset* asset);
		int GetGeneratedRefCount(int resourceID);
		void IncrementGeneratedRefCount(int resourceID);
		void DecrementGeneratedRefCount(int resourceID);
		void DeleteGeneratedResource(int resourceID);
		std::pair<int, Asset*>& GetGeneratedResource(int resourceID);
		void TestGeneratedRefCount(int refCount, int resourceID);
		Asset* GetGeneratedResourcePtr(int resourceID);

		void DeleteAssetPtr(Asset* ptr);

		Texture2D* CreateNewTexture2D(const String& filename, MipmapMode mipmap);
		Shader* CreateNewShader(const String& vFile, const String& fFile);
		Shader* CreateNewShader(const String& shaderFile);
		Model* CreateNewOBJModel(const String& filename);


	};

}