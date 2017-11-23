#include "ResourceManager.h"
#include "Resource.h"
#include "Scene\Systems\__Systems__.h"
#include "Shaders\__Shaders__.h"

namespace Ablaze
{

	ResourceManager::ResourceManager() : Object()
	{
		
	}

	ResourceManager& ResourceManager::Library()
	{
		static ResourceManager* instance = new ResourceManager();
		return *instance;
	}

	Resource<Texture2D> ResourceManager::LoadTexture2D(const String& filename, MipmapMode mipmap)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Texture2D;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", filename);
		info.AddIdentifier("MipmapMode", (int)mipmap);
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Texture2D>((Texture2D*)GetAsset(info).ptr);
		}
		return Resource<Texture2D>(CreateNewTexture2D(filename, mipmap));
	}

	Resource<Font> ResourceManager::LoadFont(const String& filename, float size)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Font;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", filename);
		info.AddIdentifier("Size", size);
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Font>((Font*)GetAsset(info).ptr);
		}
		return Resource<Font>(CreateNewFont(filename, size));
	}

	Resource<ShaderProgram> ResourceManager::LoadShaderProgram(ShaderType type, const String& filename)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::ShaderProgram;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", filename);
		info.AddIdentifier("ShaderType", (int)type);
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<ShaderProgram>((ShaderProgram*)GetAsset(info).ptr);
		}
		return Resource<ShaderProgram>(CreateNewShaderProgram(type, filename, true));
	}

	Resource<Shader> ResourceManager::LoadShader(const String& vFile, const String& fFile)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("VertexFile", vFile);
		info.AddIdentifier("FragmentFile", fFile);
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Shader>((Shader*)GetAsset(info).ptr);
		}
		return Resource<Shader>(CreateNewShader(vFile, fFile));
	}

	Resource<Shader> ResourceManager::LoadShader(const String& shaderFile)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", shaderFile);
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Shader>((Shader*)GetAsset(info).ptr);
		}
		return Resource<Shader>(CreateNewShader(shaderFile));
	}

	Resource<Shader> ResourceManager::DefaultColorShader()
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", "DefaultColorShader");
		if (!AssetExists(info))
		{
			String vSource =
#include "Shaders\Source\DefaultColor_v.glsl"
				;
			String fSource =
#include "Shaders\Source\DefaultColor_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, fSource);
			AddNewAsset(info, shader);
			Resource<Shader> res = Resource<Shader>(shader);
			return res;
		}
		return Resource<Shader>((Shader*)GetAsset(info).ptr);
	}

	Resource<Shader> ResourceManager::DefaultTextureShader()
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", "DefaultTextureShader");
		if (!AssetExists(info))
		{
			String vSource =
#include "Shaders\Source\DefaultTexture_v.glsl"
				;
			String fSource =
#include "Shaders\Source\DefaultTexture_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, fSource);
			AddNewAsset(info, shader);
			Resource<Shader> res = Resource<Shader>(shader);
			return res;
		}
		return Resource<Shader>((Shader*)GetAsset(info).ptr);
	}

	Resource<Shader> ResourceManager::LightingColorShader()
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", "LightingColorShader");
		if (!AssetExists(info))
		{
			String vSource =
#include "Shaders\Source\LightColor_v.glsl"
				;
			String fSource =
#include "Shaders\Source\LightColor_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, fSource);
			AddNewAsset(info, shader);
			Resource<Shader> res = Resource<Shader>(shader);
			Systems::Lighting().AddShader(res);
			return res;
		}
		return Resource<Shader>((Shader*)GetAsset(info).ptr);
	}

	Resource<Shader> ResourceManager::LightingTextureShader()
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", "LightingTextureShader");
		if (!AssetExists(info))
		{
			String vSource =
#include "Shaders\Source\LightTexture_v.glsl"
				;
			String fSource =
#include "Shaders\Source\LightTexture_f.glsl"
				;
			Shader* shader = Shader::FromSource(vSource, fSource);
			AddNewAsset(info, shader);
			Resource<Shader> res = Resource<Shader>(shader);
			Systems::Lighting().AddShader(res);
			return res;
		}
		return Resource<Shader>((Shader*)GetAsset(info).ptr);
	}

	Resource<Shader> ResourceManager::DefaultWireframeShader()
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", "DefaultWireframeShader");
		if (!AssetExists(info))
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
			AddNewAsset(info, shader);
			Resource<Shader> res = Resource<Shader>(shader);
			return res;
		}
		return Resource<Shader>((Shader*)GetAsset(info).ptr);
	}

	Resource<Model> ResourceManager::LoadOBJModel(const String& objFile)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::OBJModel;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", objFile);
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Model>((Model*)GetAsset(info).ptr);
		}
		return Resource<Model>(CreateNewOBJModel(objFile));
	}

	Resource<Texture2D> ResourceManager::CreateBlankTexture2D(uint width, uint height, MipmapMode mipmap)
	{
		Texture2D* texture = new Texture2D(width, height, ImageFormat::Rgba, mipmap);
		AssetLoadInfo info;
		info.Type() = AssetType::Texture2D;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Height", height);
		info.AddIdentifier("MipmapMode", (int)mipmap);
		// Don't share blank textures !!!
		AddNewAsset(info, texture);
		return Resource<Texture2D>(texture);
	}

	Resource<ShaderProgram> ResourceManager::CreateShaderProgram(ShaderType type, const String& shaderSource)
	{
		ShaderProgram* program = CreateNewShaderProgram(type, shaderSource, false);
		AssetLoadInfo info;
		info.Type() = AssetType::ShaderProgram;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Source", shaderSource);
		info.AddIdentifier("Type", (int)type);
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<ShaderProgram>((ShaderProgram*)GetAsset(info).ptr);
		}
		AddNewAsset(info, program);
		return Resource<ShaderProgram>(program);
	}

	Resource<Model> ResourceManager::CreateRectangle(float width, float height, const Color& color)
	{
		Model* rectangle = Internal::Shapes::Rectangle(width, height, color);
		AssetLoadInfo info;
		info.Type() = AssetType::Rectangle;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Height", height);
		info.AddIdentifier("Color", color.ToString());
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Model>((Model*)GetAsset(info).ptr);
		}
		AddNewAsset(info, rectangle);
		return Resource<Model>(rectangle);
	}

	Resource<Model> ResourceManager::CreateEllipse(float width, float height, const Color& color)
	{
		Model* ellipse = Internal::Shapes::Ellipse(width, height, 100, color);
		AssetLoadInfo info;
		info.Type() = AssetType::Ellipse;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Height", height);
		info.AddIdentifier("Color", color.ToString());
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Model>((Model*)GetAsset(info).ptr);
		}
		AddNewAsset(info, ellipse);
		return Resource<Model>(ellipse);
	}

	Resource<Model> ResourceManager::CreateCircle(float radius, const Color& color)
	{
		return CreateEllipse(radius * 2.0f, radius * 2.0f, color);
	}

	Resource<Model> ResourceManager::CreateCuboid(float width, float height, float depth, const Color& color)
	{
		Model* cuboid = Internal::Shapes::Cuboid(width, height, depth, color);
		AssetLoadInfo info;
		info.Type() = AssetType::Cuboid;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Height", height);
		info.AddIdentifier("Depth", depth);
		info.AddIdentifier("Color", color.ToString());
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Model>((Model*)GetAsset(info).ptr);
		}
		AddNewAsset(info, cuboid);
		return Resource<Model>(cuboid);
	}

	Resource<Model> ResourceManager::CreateSphere(float radius, const Color& color)
	{
		Model* sphere = Internal::Shapes::Sphere(radius, 1, color);
		AssetLoadInfo info;
		info.Type() = AssetType::Sphere;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Radius", radius);
		info.AddIdentifier("Color", color.ToString());
		AddNewAsset(info, sphere);
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Model>((Model*)GetAsset(info).ptr);
		}
		return Resource<Model>(sphere);
	}

	Resource<Model> ResourceManager::CreateGrid(float width, float depth, int xVertices, int zVertices, const Color& color)
	{
		Model* grid = Internal::Shapes::Grid(width, depth, xVertices, zVertices, color);
		AssetLoadInfo info;
		info.Type() = AssetType::Grid;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Depth", width);
		info.AddIdentifier("xVertices", xVertices);
		info.AddIdentifier("yVertices", zVertices);
		info.AddIdentifier("Color", color.ToString());
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Model>((Model*)GetAsset(info).ptr);
		}
		AddNewAsset(info, grid);
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

	void ResourceManager::AddNewAsset(const AssetLoadInfo& info, Asset* asset, int initialRefCount)
	{
		m_Assets[info] = { asset, initialRefCount };
		asset->Info() = info;
	}

	void ResourceManager::IncrementRefCount(const AssetLoadInfo& info, int count)
	{
		AssetPtr& asset = GetAsset(info);
		asset.ref += count;
	}

	void ResourceManager::DecrementRefCount(const AssetLoadInfo& info, int count)
	{
		AssetPtr& asset = GetAsset(info);
		asset.ref -= count;
		if (asset.ref <= 0)
		{
			DeleteAsset(info);
		}
	}

	void ResourceManager::DeleteAsset(const AssetLoadInfo& info)
	{
		AssetPtr& asset = GetAsset(info);
		delete asset.ptr;
		m_Assets.erase(info);
	}

	AssetPtr& ResourceManager::GetAsset(const AssetLoadInfo& info)
	{
		return m_Assets[info];
	}

	bool ResourceManager::AssetExists(const AssetLoadInfo& info)
	{
		return (m_Assets.find(info) != m_Assets.end());
	}

	Texture2D* ResourceManager::CreateNewTexture2D(const String& filename, MipmapMode mipmap)
	{
		Texture2D* tex = new Texture2D(filename, mipmap);
		AssetLoadInfo info;
		info.Type() = AssetType::Texture2D;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", filename);
		info.AddIdentifier("MipmapMode", (int)mipmap);
		AddNewAsset(info, tex);
		return tex;
	}

	Font* ResourceManager::CreateNewFont(const String& filename, float size)
	{
		Font* font = new Font(filename, size);
		AssetLoadInfo info;
		info.Type() = AssetType::Font;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", filename);
		info.AddIdentifier("Size", size);
		AddNewAsset(info, font);
		return font;
	}

	Shader* ResourceManager::CreateNewShader(const String& vFile, const String& fFile)
	{
		Shader* shader = Shader::FromFile(vFile, fFile);
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("VertexFile", vFile);
		info.AddIdentifier("FragmentFile", fFile);
		AddNewAsset(info, shader);
		return shader;
	}

	Shader* ResourceManager::CreateNewShader(const String& shaderFile)
	{
		Shader* shader = Shader::FromFile(shaderFile);
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", shaderFile);
		AddNewAsset(info, shader);
		return shader;
	}

	ShaderProgram* ResourceManager::CreateNewShaderProgram(ShaderType type, const String& fileOrSource, bool isFile)
	{
		if (isFile)
		{
			ShaderProgram* program = ShaderProgram::FromFile(type, fileOrSource);
			AssetLoadInfo info;
			info.Type() = AssetType::ShaderProgram;
			info.LoadMethod() = LoadType::Loaded;
			info.AddIdentifier("Filename", fileOrSource);
			info.AddIdentifier("ShaderType", (int)type);
			AddNewAsset(info, program);
			return program;
		}
		ShaderProgram* program = ShaderProgram::FromSource(type, fileOrSource);
		AssetLoadInfo info;
		info.Type() = AssetType::ShaderProgram;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Source", fileOrSource);
		info.AddIdentifier("ShaderType", (int)type);
		AddNewAsset(info, program);
		return program;
	}

	Model* ResourceManager::CreateNewOBJModel(const String& filename)
	{
		Model* model = new Model(filename);
		AssetLoadInfo info;
		info.Type() = AssetType::OBJModel;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", filename);
		AddNewAsset(info, model);
		return model;
	}

}