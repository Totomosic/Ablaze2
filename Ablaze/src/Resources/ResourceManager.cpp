#include "ResourceManager.h"
#include "Resource.h"
#include "Scene\Systems\__Systems__.h"
#include "Shaders\__Shaders__.h"

namespace Ablaze
{

	ResourceManager::ResourceManager()
	{
		
	}

	Resource<Texture2D> ResourceManager::LoadTexture2D(const String& filename, MipmapMode mipmap)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Texture2D;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", filename);
		info.AddIdentifier("MipmapMode", (int)mipmap);
		return LoadTexture2DAsset(info);
	}

	Resource<Font> ResourceManager::LoadFont(const String& filename, float size)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Font;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", filename);
		info.AddIdentifier("Size", size);
		return LoadFontAsset(info);
	}

	Resource<Shader> ResourceManager::LoadShader(const String& vFile, const String& fFile)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("VertexFile", vFile);
		info.AddIdentifier("FragmentFile", fFile);
		return LoadShaderAsset(info);
	}

	Resource<Shader> ResourceManager::LoadShader(const String& shaderFile)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Shader;
		info.LoadMethod() = LoadType::Loaded;
		info.AddIdentifier("Filename", shaderFile);
		return LoadShaderAsset(info);
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
		return LoadModelAsset(info);
	}

	Resource<Texture2D> ResourceManager::CreateBlankTexture2D(uint width, uint height, MipmapMode mipmap)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Texture2D;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Height", height);
		info.AddIdentifier("MipmapMode", (int)mipmap);
		return LoadTexture2DAsset(info);
	}

	Resource<Model> ResourceManager::CreateRectangle(float width, float height, const Color& color)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Rectangle;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Height", height);
		return LoadModelAsset(info);
	}

	Resource<Model> ResourceManager::CreateEllipse(float width, float height, const Color& color)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Ellipse;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Height", height);
		return LoadModelAsset(info);
	}

	Resource<Model> ResourceManager::CreateCircle(float radius, const Color& color)
	{
		return CreateEllipse(radius * 2.0f, radius * 2.0f, color);
	}

	Resource<Model> ResourceManager::CreateCuboid(float width, float height, float depth, const Color& color)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Cuboid;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Height", height);
		info.AddIdentifier("Depth", depth);
		return LoadModelAsset(info);
	}

	Resource<Model> ResourceManager::CreateSphere(float radius, const Color& color)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Sphere;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Radius", radius);
		info.AddIdentifier("Color", color.ToString());
		return LoadModelAsset(info);
	}

	Resource<Model> ResourceManager::CreateGrid(float width, float depth, int xVertices, int zVertices, const Color& color)
	{
		AssetLoadInfo info;
		info.Type() = AssetType::Grid;
		info.LoadMethod() = LoadType::Generated;
		info.AddIdentifier("Width", width);
		info.AddIdentifier("Depth", depth);
		info.AddIdentifier("xVertices", xVertices);
		info.AddIdentifier("zVertices", zVertices);
		info.AddIdentifier("Color", color.ToString());
		return LoadModelAsset(info);
	}

	Resource<Model> ResourceManager::CreatePlane(float width, float depth, const Color& color)
	{
		return CreateGrid(width, depth, 2, 2, color);
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

	Texture2D* ResourceManager::CreateNewTexture2D(const AssetLoadInfo& info)
	{
		Texture2D* tex = new Texture2D(info["Filename"], (MipmapMode)stoi(info["MipmapMode"]));
		AddNewAsset(info, tex);
		return tex;
	}

	Font* ResourceManager::CreateNewFont(const AssetLoadInfo& info)
	{
		Font* font = new Font(info["Filename"], stof(info["Size"]));
		AddNewAsset(info, font);
		return font;
	}

	Shader* ResourceManager::CreateNewShader(const AssetLoadInfo& info)
	{
		Shader* shader = nullptr;
		if (info.IdentifierCount() == 1)
		{
			shader = Shader::FromFile(info["Filename"]);
		}
		else
		{
			shader = Shader::FromFile(info["VertexFile"], info["FragmentFile"]);
		}
		AddNewAsset(info, shader);
		return shader;
	}

	Model* ResourceManager::CreateNewOBJModel(const AssetLoadInfo& info)
	{
		Model* model = new Model(info["Filename"]);
		AddNewAsset(info, model);
		return model;
	}

	Resource<Model> ResourceManager::LoadModelAsset(const AssetLoadInfo& info)
	{
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Model>((Model*)GetAsset(info).ptr);
		}
		if (info.Type() == AssetType::OBJModel)
		{
			return Resource<Model>(CreateNewOBJModel(info));
		}
		else if (info.Type() == AssetType::Cuboid)
		{
			Model* cuboid = Internal::Shapes::Cuboid(stof(info["Width"]), stof(info["Height"]), stof(info["Depth"]));
			AddNewAsset(info, cuboid);
			return Resource<Model>(cuboid);
		}
		else if (info.Type() == AssetType::Grid)
		{
			Model* grid = Internal::Shapes::Grid(stof(info["Width"]), stof(info["Depth"]), stoi(info["xVertices"]), stoi(info["zVertices"]));
			AddNewAsset(info, grid);
			return Resource<Model>(grid);
		}
		else if (info.Type() == AssetType::Sphere)
		{
			Model* sphere = Internal::Shapes::Sphere(stof(info["Radius"]), 100);
			AddNewAsset(info, sphere);
			return Resource<Model>(sphere);
		}
		else if (info.Type() == AssetType::Ellipse)
		{
			Model* ellipse = Internal::Shapes::Ellipse(stof(info["Width"]), stof(info["Height"]), 100);
			AddNewAsset(info, ellipse);
			return Resource<Model>(ellipse);
		}
		else if (info.Type() == AssetType::Rectangle)
		{
			Model* rectangle = Internal::Shapes::Rectangle(stof(info["Width"]), stof(info["Height"]));
			AddNewAsset(info, rectangle);
			return Resource<Model>(rectangle);
		}
	}

	Resource<Shader> ResourceManager::LoadShaderAsset(const AssetLoadInfo& info)
	{
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Shader>((Shader*)GetAsset(info).ptr);
		}
		if (info.LoadMethod() == LoadType::Loaded)
		{
			if (info["Filename"] == "DefaultColorShader")
			{
				return DefaultColorShader();
			}
			else if (info["Filename"] == "DefaultTextureShader")
			{
				return DefaultTextureShader();
			}
			else if (info["Filename"] == "LightingColorShader")
			{
				return LightingColorShader();
			}
			else if (info["Filename"] == "LightingTextureShader")
			{
				return LightingTextureShader();
			}
			else if (info["Filename"] == "DefaultWireframeShader")
			{
				return DefaultWireframeShader();
			}
			return Resource<Shader>(CreateNewShader(info));
		}
	}

	Resource<Texture2D> ResourceManager::LoadTexture2DAsset(const AssetLoadInfo& info)
	{
		if (info.LoadMethod() == LoadType::Generated)
		{
			int width = stoi(info["Width"]);
			int height = stoi(info["Height"]);
			MipmapMode mip = (MipmapMode)stoi(info["MipmapMode"]);
			Texture2D* texture = new Texture2D((uint)width, (uint)height, ImageFormat::Rgba, mip);
			AddNewAsset(info, texture);
			return Resource<Texture2D>(texture);
		}
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Texture2D>((Texture2D*)GetAsset(info).ptr);
		}		
		return Resource<Texture2D>(CreateNewTexture2D(info));
	}

	Resource<Font> ResourceManager::LoadFontAsset(const AssetLoadInfo& info)
	{
		if (AssetExists(info))
		{
			IncrementRefCount(info);
			return Resource<Font>((Font*)GetAsset(info).ptr);
		}
		return Resource<Font>(CreateNewFont(info));
	}

}