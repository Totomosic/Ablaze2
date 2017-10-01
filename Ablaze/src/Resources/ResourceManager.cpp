#include "ResourceManager.h"
#include "Resource.h"

namespace Ablaze
{

	ResourceManager* ResourceManager::s_Instance = nullptr;

	ResourceManager::ResourceManager() : Object()
	{
	
	}

	ResourceManager& ResourceManager::Library()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new ResourceManager();
		}
		return *s_Instance;
	}

	Resource<Texture2D> ResourceManager::CreateBlankTexture2D(uint width, uint height, MipmapMode mipmap)
	{
		return Resource<Texture2D>(new Texture2D(width, height, ImageFormat::Rgba, mipmap));
	}

	Resource<Texture2D> ResourceManager::LoadTexture2D(const String& filename, MipmapMode mipmap)
	{
		if (FileExists(filename))
		{
			IncrementRefCount(filename);
			return Resource<Texture2D>((Texture2D*)GetResourcePtr(filename));
		}
		return Resource<Texture2D>(CreateNewTexture2D(filename, mipmap));
	}

	Resource<Shader> ResourceManager::LoadShader(const String& vFile, const String& fFile)
	{
		if (FileExists(vFile))
		{
			IncrementRefCount(vFile);
			return Resource<Shader>((Shader*)GetResourcePtr(vFile));
		}
		return Resource<Shader>(CreateNewShader(vFile, fFile));
	}

	Resource<Model> ResourceManager::LoadOBJModel(const String& objFile)
	{
		if (FileExists(objFile))
		{
			IncrementRefCount(objFile);
			return Resource<Model>((Model*)GetResourcePtr(objFile));
		}
		return Resource<Model>(CreateNewOBJModel(objFile));
	}

	Resource<Model> ResourceManager::CreateRectangle(float width, float height, const Color& color)
	{
		return Resource<Model>(Internal::Shapes::Rectangle(width, height, color));
	}

	String ResourceManager::ToString() const
	{
		return "ResourceManager";
	}

	bool ResourceManager::FileExists(const String& filename)
	{
		return m_Resources.find(filename) != m_Resources.end();
	}

	int ResourceManager::GetRefCount(const String& filename)
	{
		return GetResource(filename).first;
	}

	void ResourceManager::IncrementRefCount(const String& filename)
	{
		GetResource(filename).first++;
	}

	void ResourceManager::DecrementRefCount(const String& filename)
	{
		int& count = GetResource(filename).first;
		count--;
		TestRefCount(count, filename);
	}

	void ResourceManager::DeleteResource(const String& filename)
	{
		auto res = GetResource(filename);
		delete res.second;
		m_Resources.erase(filename);
	}

	std::pair<int, Asset*>& ResourceManager::GetResource(const String& filename)
	{
		return m_Resources[filename];
	}

	void ResourceManager::CreateNewResource(const String& filename, Asset* asset)
	{
		m_Resources[filename] = std::pair<int, Asset*>(1, asset);
	}

	void ResourceManager::TestRefCount(int refCount, const String& filename)
	{
		if (refCount <= 0)
		{
			DeleteResource(filename);
		}
	}

	Asset* ResourceManager::GetResourcePtr(const String& filename)
	{
		return GetResource(filename).second;
	}

	void ResourceManager::DeleteAssetPtr(Asset* ptr)
	{
		delete ptr;
	}

	Texture2D* ResourceManager::CreateNewTexture2D(const String& filename, MipmapMode mipmap)
	{
		Texture2D* tex = new Texture2D(filename, mipmap);
		CreateNewResource(filename, tex);
		return tex;
	}

	Shader* ResourceManager::CreateNewShader(const String& vFile, const String& fFile)
	{
		Shader* shader = Shader::FromFile(vFile, fFile);
		CreateNewResource(vFile, shader);
		return shader;
	}

	Model* ResourceManager::CreateNewOBJModel(const String& filename)
	{
		Model* model = new Model(filename);
		CreateNewResource(filename, model);
		return model;
	}

}