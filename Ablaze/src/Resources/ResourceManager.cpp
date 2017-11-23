#include "ResourceManager.h"
#include "Resource.h"
#include "Scene\Systems\__Systems__.h"
#include "Shaders\__Shaders__.h"

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
		Texture2D* texture = new Texture2D(width, height, ImageFormat::Rgba, mipmap);
		CreateNewGeneratedResource(texture);
		IncrementGeneratedRefCount(texture->m_ResourceID);
		return Resource<Texture2D>(texture);
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

	Resource<Font> ResourceManager::LoadFont(const String& filename, float size)
	{
		if (LoadedResourceExists(filename))
		{
			IncrementLoadedRefCount(filename);
			return Resource<Font>((Font*)GetLoadedResourcePtr(filename));
		}
		return Resource<Font>(CreateNewFont(filename, size));
	}

	Resource<ShaderProgram> ResourceManager::LoadShaderProgram(ShaderType type, const String& filename)
	{
		if (LoadedResourceExists(filename))
		{
			IncrementLoadedRefCount(filename);
			return Resource<ShaderProgram>((ShaderProgram*)GetLoadedResourcePtr(filename));
		}
		return Resource<ShaderProgram>(CreateNewShaderProgram(type, filename, true));
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

	Resource<Shader> ResourceManager::DefaultColorShader()
	{
		if (!LoadedResourceExists("DefaultColorShader"))
		{
			String vSource =
#include "Shaders\Source\DefaultColor_v.glsl"
				;
			String fSource =
#include "Shaders\Source\DefaultColor_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, fSource);
			CreateNewLoadedResource("DefaultColorShader", shader);
			IncrementLoadedRefCount("DefaultColorShader");
			return Resource<Shader>(shader);
		}
		return Resource<Shader>((Shader*)GetLoadedResourcePtr("DefaultColorShader"));
	}

	Resource<Shader> ResourceManager::DefaultTextureShader()
	{
		if (!LoadedResourceExists("DefaultTextureShader"))
		{
			String vSource =
#include "Shaders\Source\DefaultTexture_v.glsl"
				;
			String fSource =
#include "Shaders\Source\DefaultTexture_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, fSource);
			CreateNewLoadedResource("DefaultTextureShader", shader);
			IncrementLoadedRefCount("DefaultTextureShader");
			return Resource<Shader>(shader);
		}
		return Resource<Shader>((Shader*)GetLoadedResourcePtr("DefaultTextureShader"));
	}

	Resource<Shader> ResourceManager::LightingColorShader()
	{
		if (!LoadedResourceExists("LightingColorShader"))
		{
			String vSource =
#include "Shaders\Source\LightColor_v.glsl"
				;
			String fSource =
#include "Shaders\Source\LightColor_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, fSource);
			CreateNewLoadedResource("LightingColorShader", shader);
			IncrementLoadedRefCount("LightingColorShader");
			Resource<Shader> res = Resource<Shader>(shader);
			Systems::Lighting().AddShader(res);
			return res;
		}
		return Resource<Shader>((Shader*)GetLoadedResourcePtr("LightingColorShader"));
	}

	Resource<Shader> ResourceManager::LightingTextureShader()
	{
		if (!LoadedResourceExists("LightingTextureShader"))
		{
			String vSource =
#include "Shaders\Source\LightTexture_v.glsl"
				;
			String fSource =
#include "Shaders\Source\LightTexture_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, fSource);
			CreateNewLoadedResource("LightingTextureShader", shader);
			IncrementLoadedRefCount("LightingTextureShader");
			Resource<Shader> res = Resource<Shader>(shader);
			Systems::Lighting().AddShader(res);
			return res;
		}
		return Resource<Shader>((Shader*)GetLoadedResourcePtr("LightingTextureShader"));
	}

	Resource<Shader> ResourceManager::DefaultWireframeShader()
	{
		if (!LoadedResourceExists("DefaultWireframeShader"))
		{
			String vSource =
#include "Shaders\Source\DefaultWireframe_v.glsl"
				;
			String gSource =
#include "Shaders\Source\DefaultWireframe_g.glsl"
				;
			String fSource =
#include "Shaders\Source\DefaultWireframe_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, gSource, fSource);
			CreateNewLoadedResource("DefaultWireframeShader", shader);
			IncrementLoadedRefCount("DefaultWireframeShader");
			Resource<Shader> res = Resource<Shader>(shader);
			Systems::Lighting().AddShader(res);
			return res;
		}
		return Resource<Shader>((Shader*)GetLoadedResourcePtr("LightingTextureShader"));
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

	Resource<ShaderProgram> ResourceManager::CreateShaderProgram(ShaderType type, const String& shaderSource)
	{
		ShaderProgram* program = CreateNewShaderProgram(type, shaderSource, false);
		return Resource<ShaderProgram>(program);
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

	Resource<Model> ResourceManager::CreateSphere(float radius, const Color& color)
	{
		Model* sphere = Internal::Shapes::Sphere(radius, 1, color);
		CreateNewGeneratedResource(sphere);
		return Resource<Model>(sphere);
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
		asset->m_AssetType = AssetType::Loaded;
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
		return m_GeneratedResources[resourceID] != nullptr && m_GeneratedResources[resourceID]->second != nullptr;
	}

	void ResourceManager::CreateNewGeneratedResource(Asset* asset)
	{
		m_GeneratedResources[m_GeneratedResourceCount] = new std::pair<int, Asset*>(1, asset);
		asset->SetResourceID(m_GeneratedResourceCount);
		m_GeneratedResourceCount++;
		asset->m_AssetType = AssetType::Generated;
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

	Font* ResourceManager::CreateNewFont(const String& filename, float size)
	{
		Font* font = new Font(filename, size);
		CreateNewLoadedResource(filename, font);
		return font;
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

	ShaderProgram* ResourceManager::CreateNewShaderProgram(ShaderType type, const String& fileOrSource, bool isFile)
	{
		if (isFile)
		{
			ShaderProgram* program = ShaderProgram::FromFile(type, fileOrSource);
			CreateNewLoadedResource(fileOrSource, program);
			return program;
		}
		ShaderProgram* program = ShaderProgram::FromSource(type, fileOrSource);
		CreateNewGeneratedResource(program);
		return program;
	}

	Model* ResourceManager::CreateNewOBJModel(const String& filename)
	{
		Model* model = new Model(filename);
		CreateNewLoadedResource(filename, model);
		return model;
	}

}