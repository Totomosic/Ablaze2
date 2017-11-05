#include "ResourceManager.h"
#include "Resource.h"
#include "Utils\FileSystem\__FileSystem__.h"

namespace Ablaze
{

	ResourceManager::ResourceManager() : Object(),
		m_MaxGenResources(5000), m_LoadedResources(), m_GeneratedResources(new std::pair<int, Asset*>*[m_MaxGenResources]), m_GeneratedResourceCount(0)
	{
		for (int i = 0; i < m_MaxGenResources; i++)
		{
			m_GeneratedResources[i] = nullptr;
		}
	}

	ResourceManager& ResourceManager::Library()
	{
		static ResourceManager* instance = new ResourceManager();
		return *instance;
	}

	Resource<Texture2D> ResourceManager::CreateBlankTexture2D(uint width, uint height, MipmapMode mipmap)
	{
		return Resource<Texture2D>(new Texture2D(width, height, ImageFormat::Rgba, mipmap));
	}

	Resource<Texture2D> ResourceManager::LoadTexture2D(const String& filename, MipmapMode mipmap)
	{
		if (LoadedResourceExists(filename))
		{
			IncrementLoadedRefCount(filename);
			return Resource<Texture2D>((Texture2D*)GetLoadedResourcePtr(filename));
		}
		return Resource<Texture2D>(CreateNewTexture2D(filename, mipmap));
	}

	Resource<Shader> ResourceManager::LoadShader(const String& vFile, const String& fFile)
	{
		if (LoadedResourceExists(vFile))
		{
			IncrementLoadedRefCount(vFile);
			return Resource<Shader>((Shader*)GetLoadedResourcePtr(vFile));
		}
		return Resource<Shader>(CreateNewShader(vFile, fFile));
	}

	Resource<Shader> ResourceManager::LoadShader(const String& shaderFile)
	{
		if (LoadedResourceExists(shaderFile))
		{
			IncrementLoadedRefCount(shaderFile);
			return Resource<Shader>((Shader*)GetLoadedResourcePtr(shaderFile));
		}
		return Resource<Shader>(CreateNewShader(shaderFile));
	}

	Resource<Model> ResourceManager::LoadOBJModel(const String& objFile)
	{
		if (LoadedResourceExists(objFile))
		{
			IncrementLoadedRefCount(objFile);
			return Resource<Model>((Model*)GetLoadedResourcePtr(objFile));
		}
		return Resource<Model>(CreateNewOBJModel(objFile));
	}

	Resource<Model> ResourceManager::CreateRectangle(float width, float height, const Color& color)
	{
		Model* rectangle = Internal::Shapes::Rectangle(width, height, color);
		CreateNewGeneratedResource(rectangle);
		return Resource<Model>(rectangle);
	}

	Resource<Model> ResourceManager::CreateEllipse(float width, float height, const Color& color)
	{
		Model* ellipse = Internal::Shapes::Ellipse(width, height, 100, color);
		CreateNewGeneratedResource(ellipse);
		return Resource<Model>(ellipse);
	}

	Resource<Model> ResourceManager::CreateCircle(float radius, const Color& color)
	{
		return CreateEllipse(radius * 2.0f, radius * 2.0f, color);
	}

	Resource<Model> ResourceManager::CreateCuboid(float width, float height, float depth, const Color& color)
	{
		Model* cuboid = Internal::Shapes::Cuboid(width, height, depth, color);
		CreateNewGeneratedResource(cuboid);
		return Resource<Model>(cuboid);
	}

	Resource<Model> ResourceManager::CreateGrid(float width, float depth, int xVertices, int zVertices, const Color& color)
	{
		Model* grid = Internal::Shapes::Grid(width, depth, xVertices, zVertices, color);
		CreateNewGeneratedResource(grid);
		return Resource<Model>(grid);
	}

	Resource<Model> ResourceManager::CreatePlane(float width, float depth, const Color& color)
	{
		return CreateGrid(width, depth, 2, 2, color);
	}

	String ResourceManager::ToString() const
	{
		return "ResourceManager";
	}

	bool ResourceManager::LoadedResourceExists(const String& filename)
	{
		return m_LoadedResources.find(filename) != m_LoadedResources.end();
	}

	int ResourceManager::GetLoadedRefCount(const String& filename)
	{
		return GetLoadedResource(filename).first;
	}

	void ResourceManager::IncrementLoadedRefCount(const String& filename)
	{
		GetLoadedResource(filename).first++;
	}

	void ResourceManager::DecrementLoadedRefCount(const String& filename)
	{
		int& count = GetLoadedResource(filename).first;
		count--;
		TestLoadedRefCount(count, filename);
	}

	void ResourceManager::DeleteLoadedResource(const String& filename)
	{
		auto res = GetLoadedResource(filename);
		m_LoadedResources.erase(filename);
		delete res.second;
	}

	std::pair<int, Asset*>& ResourceManager::GetLoadedResource(const String& filename)
	{
		return m_LoadedResources[filename];
	}

	void ResourceManager::CreateNewLoadedResource(const String& filename, Asset* asset)
	{
		m_LoadedResources[filename] = std::pair<int, Asset*>(1, asset);
	}

	void ResourceManager::TestLoadedRefCount(int refCount, const String& filename)
	{
		if (refCount <= 0)
		{
			DeleteLoadedResource(filename);
		}
	}

	Asset* ResourceManager::GetLoadedResourcePtr(const String& filename)
	{
		return GetLoadedResource(filename).second;
	}

	bool ResourceManager::GeneratedResourceExists(int resourceID)
	{
		return m_GeneratedResources[resourceID]->second != nullptr;
	}

	void ResourceManager::CreateNewGeneratedResource(Asset* asset)
	{
		m_GeneratedResources[m_GeneratedResourceCount] = new std::pair<int, Asset*>(1, asset);
		asset->SetResourceID(m_GeneratedResourceCount);
		m_GeneratedResourceCount++;
	}

	int ResourceManager::GetGeneratedRefCount(int resourceID)
	{
		return GetGeneratedResource(resourceID).first;
	}

	std::pair<int, Asset*>& ResourceManager::GetGeneratedResource(int resourceID)
	{
		return *(m_GeneratedResources[resourceID]);
	}

	void ResourceManager::IncrementGeneratedRefCount(int resourceID)
	{
		GetGeneratedResource(resourceID).first++;
	}

	void ResourceManager::DecrementGeneratedRefCount(int resourceID)
	{
		int& ref = GetGeneratedResource(resourceID).first;
		ref--;
		TestGeneratedRefCount(ref, resourceID);
	}

	void ResourceManager::DeleteGeneratedResource(int resourceID)
	{
		std::pair<int, Asset*>* res = &GetGeneratedResource(resourceID);
		DeleteAssetPtr(res->second);
		delete res;
		m_GeneratedResources[resourceID] = nullptr;
	}

	void ResourceManager::TestGeneratedRefCount(int refCount, int resourceID)
	{
		if (refCount <= 0)
		{
			DeleteGeneratedResource(resourceID);
		}
	}

	Asset* ResourceManager::GetGeneratedResourcePtr(int resourceID)
	{
		return GetGeneratedResource(resourceID).second;
	}

	void ResourceManager::DeleteAssetPtr(Asset* ptr)
	{
		delete ptr;
	}

	Texture2D* ResourceManager::CreateNewTexture2D(const String& filename, MipmapMode mipmap)
	{
		Texture2D* tex = new Texture2D(filename, mipmap);
		CreateNewLoadedResource(filename, tex);
		return tex;
	}

	Shader* ResourceManager::CreateNewShader(const String& vFile, const String& fFile)
	{
		Shader* shader = Shader::FromFile(vFile, fFile);
		CreateNewLoadedResource(vFile, shader);
		return shader;
	}

	Shader* ResourceManager::CreateNewShader(const String& shaderFile)
	{
		Shader* shader = Shader::FromFile(shaderFile);
		CreateNewLoadedResource(shaderFile, shader);
		return shader;
	}

	Model* ResourceManager::CreateNewOBJModel(const String& filename)
	{
		Model* model = new Model(filename);
		CreateNewLoadedResource(filename, model);
		return model;
	}

}