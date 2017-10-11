#pragma once
#include "Common.h"
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
		std::unordered_map<String, std::pair<int, Asset*>> m_Resources;

	private:
		ResourceManager();

	public:
		static ResourceManager& Library();

	public:
		Resource<Texture2D> CreateBlankTexture2D(uint width, uint height, MipmapMode mipmap = MipmapMode::Disabled);

		Resource<Texture2D> LoadTexture2D(const String& filename, MipmapMode mipmap = MipmapMode::Enabled);
		Resource<Shader> LoadShader(const String& vFile, const String& fFile);
		Resource<Model> LoadOBJModel(const String& objFile);

		Resource<Model> CreateRectangle(float width, float height, const Color& color = Color::White());

		String ToString() const override;

		template<typename> friend class Resource;

	private:
		bool FileExists(const String& filename);
		int GetRefCount(const String& filename);
		void IncrementRefCount(const String& filename);
		void DecrementRefCount(const String& filename);
		void DeleteResource(const String& filename);
		std::pair<int, Asset*>& GetResource(const String& filename);
		void CreateNewResource(const String& filename, Asset* asset);
		void TestRefCount(int refCount, const String& filename);
		Asset* GetResourcePtr(const String& filename);

		void DeleteAssetPtr(Asset* ptr);

		Texture2D* CreateNewTexture2D(const String& filename, MipmapMode mipmap);
		Shader* CreateNewShader(const String& vFile, const String& fFile);
		Model* CreateNewOBJModel(const String& filename);


	};

}