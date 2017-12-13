#include "ResourceManager.h"
#include "Shaders\__Shaders__.h"
#include "Scene\Systems\__Systems__.h"

namespace Ablaze
{

	ResourceManager::ResourceManager()
	{
		LoadDefaultColor();
		LoadDefaultTexture();
		LoadLightColor();
		LoadLightTexture();
		LoadDefaultFont();

		m_Square = CreateSquare();
		m_Circle = CreateCircle();
		m_Cube = CreateCube();
		m_Sphere = CreateSphere();
		m_Plane = CreatePlane();

		Systems::Lighting().AddShader(m_LightColor);
		Systems::Lighting().AddShader(m_LightTexture);
	}

	void ResourceManager::Terminate()
	{
		delete &Instance();
	}

	std::shared_ptr<Shader> ResourceManager::LoadShader(const String& shaderFile)
	{
		Shader* shader = Shader::FromFile(shaderFile);
		return std::shared_ptr<Shader>(shader);
	}

	std::shared_ptr<Shader> ResourceManager::LoadShader(const String& vFile, const String& fFile)
	{
		Shader* shader = Shader::FromFile(vFile, fFile);
		return std::shared_ptr<Shader>(shader);
	}

	std::shared_ptr<Shader> ResourceManager::CreateShader(const String& vSource, const String& fSource)
	{
		Shader* shader = Shader::FromSource(vSource, fSource);
		return std::shared_ptr<Shader>(shader);
	}

	std::shared_ptr<Shader> ResourceManager::CreateShader(const String& vSource, const String& gSource, const String& fSource)
	{
		Shader* shader = Shader::FromSource(vSource, gSource, fSource);
		return std::shared_ptr<Shader>(shader);
	}

	std::shared_ptr<Shader> ResourceManager::DefaultColorShader()
	{
		return m_DefaultColor;
	}

	std::shared_ptr<Shader> ResourceManager::DefaultTextureShader()
	{
		return m_DefaultTexture;
	}

	std::shared_ptr<Shader> ResourceManager::LightingColorShader()
	{
		return m_LightColor;
	}

	std::shared_ptr<Shader> ResourceManager::LightingTextureShader()
	{
		return m_LightTexture;
	}

	std::shared_ptr<Shader> ResourceManager::DefaultFontShader()
	{
		return m_DefaultFont;
	}


	std::shared_ptr<Texture2D> ResourceManager::LoadTexture2D(const String& textureFile, MipmapMode mipmap)
	{
		if (Texture2DExists(textureFile))
		{
			return m_Texture2Ds[textureFile];
		}
		return AddTexture2D(textureFile, new Texture2D(textureFile, mipmap));
	}

	std::shared_ptr<Texture2D> ResourceManager::CreateBlankTexture2D(int width, int height, MipmapMode mipmap)
	{
		return std::make_shared<Texture2D>(width, height, ImageFormat::Rgba, mipmap);
	}

	std::shared_ptr<Font> ResourceManager::LoadFont(const String& fontFile, float size)
	{
		if (FontExists(fontFile + std::to_string(size)))
		{
			return m_Fonts[fontFile + std::to_string(size)];
		}
		return AddFont(fontFile + std::to_string(size), new Font(fontFile, size));
	}


	std::shared_ptr<Model> ResourceManager::LoadModel(const String& objModelFile)
	{
		Model* model = new Model(objModelFile);
		return std::shared_ptr<Model>(model);
	}

	std::shared_ptr<Model> ResourceManager::LoadTextModel(const String& text, const std::shared_ptr<Font>& font, const Color& color, TextAlignmentH horizontal, TextAlignmentV vertical)
	{
		Model* model = font->CreateModel(text, color, horizontal, vertical);
		return std::shared_ptr<Model>(model);
	}

	std::shared_ptr<Model> ResourceManager::CreateSquare(const Color& color)
	{
		Model* model = Internal::Shapes::Rectangle(1, 1, color);
		return std::shared_ptr<Model>(model);
	}

	std::shared_ptr<Model> ResourceManager::CreateCircle(const Color& color)
	{
		Model* model = Internal::Shapes::Ellipse(2, 2, 100, color);
		return std::shared_ptr<Model>(model);
	}

	std::shared_ptr<Model> ResourceManager::CreateCube(const Color& color)
	{
		Model* model = Internal::Shapes::Cuboid(1, 1, 1, color);
		return std::shared_ptr<Model>(model);
	}

	std::shared_ptr<Model> ResourceManager::CreateSphere(const Color& color)
	{
		Model* model = Internal::Shapes::Sphere(1, 10, color);
		return std::shared_ptr<Model>(model);
	}

	std::shared_ptr<Model> ResourceManager::CreateGrid(int xVerts, int zVerts, const Color& color)
	{
		Model* model = Internal::Shapes::Grid(1, 1, xVerts, zVerts, color);
		return std::shared_ptr<Model>(model);
	}

	std::shared_ptr<Model> ResourceManager::CreatePlane(const Color& color)
	{
		return CreateGrid(2, 2, color);
	}


	std::shared_ptr<Model> ResourceManager::Square()
	{
		return m_Square;
	}

	std::shared_ptr<Model> ResourceManager::Circle()
	{
		return m_Circle;
	}

	std::shared_ptr<Model> ResourceManager::Cube()
	{
		return m_Cube;
	}

	std::shared_ptr<Model> ResourceManager::Sphere()
	{
		return m_Sphere;
	}

	std::shared_ptr<Model> ResourceManager::Plane()
	{
		return m_Plane;
	}


	bool ResourceManager::ModelExists(const String& filename)
	{
		return (m_Models.find(filename) != m_Models.end());
	}

	bool ResourceManager::Texture2DExists(const String& filename)
	{
		return (m_Texture2Ds.find(filename) != m_Texture2Ds.end());
	}

	bool ResourceManager::FontExists(const String& filename)
	{
		return (m_Fonts.find(filename) != m_Fonts.end());
	}

	std::shared_ptr<Model> ResourceManager::AddModel(const String& filename, Model* model)
	{
		std::shared_ptr<Model> m = std::shared_ptr<Model>(model);
		m_Models[filename] = m;
		return m;
	}

	std::shared_ptr<Texture2D> ResourceManager::AddTexture2D(const String& filename, Texture2D* texture)
	{
		std::shared_ptr<Texture2D> tex = std::shared_ptr<Texture2D>(texture);
		m_Texture2Ds[filename] = tex;
		return tex;
	}

	std::shared_ptr<Font> ResourceManager::AddFont(const String& filename, Font* font)
	{
		std::shared_ptr<Font> f = std::shared_ptr<Font>(font);
		m_Fonts[filename] = f;
		return f;
	}

	void ResourceManager::LoadDefaultColor()
	{
		String vSource =
#include "Shaders\Source\DefaultColor_v.glsl"
			;
		String fSource =
#include "Shaders\Source\DefaultColor_f.glsl"
			;
		m_DefaultColor = CreateShader(vSource, fSource);
	}

	void ResourceManager::LoadDefaultTexture()
	{
		String vSource =
#include "Shaders\Source\DefaultTexture_v.glsl"
			;
		String fSource =
#include "Shaders\Source\DefaultTexture_f.glsl"
			;
		m_DefaultTexture = CreateShader(vSource, fSource);
	}

	void ResourceManager::LoadLightColor()
	{
		String vSource =
#include "Shaders\Source\LightColor_v.glsl"
			;
		String fSource =
#include "Shaders\Source\LightColor_f.glsl"
			;
		m_LightColor = CreateShader(vSource, fSource);
	}

	void ResourceManager::LoadLightTexture()
	{
		String vSource =
#include "Shaders\Source\LightTexture_v.glsl"
			;
		String fSource =
#include "Shaders\Source\LightTexture_f.glsl"
			;
		m_LightTexture = CreateShader(vSource, fSource);
	}

	void ResourceManager::LoadDefaultFont()
	{
		String vSource =
#include "Shaders\Source\DefaultFont_v.glsl"
			;
		String fSource =
#include "Shaders\Source\DefaultFont_f.glsl"
			;
		m_DefaultFont = CreateShader(vSource, fSource);
	}

}