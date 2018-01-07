#include "ResourceManager.h"
#include "Shaders\__Shaders__.h"
#include "Scene\Systems\__Systems__.h"

namespace Ablaze
{

	Shader* ResourceManager::s_DefaultColor = nullptr;
	Shader* ResourceManager::s_DefaultTexture = nullptr;
	Shader* ResourceManager::s_LightColor = nullptr;
	Shader* ResourceManager::s_LightTexture = nullptr;
	Shader* ResourceManager::s_DefaultFont = nullptr;

	Model* ResourceManager::s_Square = nullptr;
	Model* ResourceManager::s_Circle = nullptr;
	Model* ResourceManager::s_Cube = nullptr;
	Model* ResourceManager::s_Sphere = nullptr;
	Model* ResourceManager::s_Plane = nullptr;

	std::unordered_map<String, Texture2D*> ResourceManager::s_Texture2Ds = std::unordered_map<String, Texture2D*>();
	std::unordered_map<String, Model*> ResourceManager::s_Models = std::unordered_map<String, Model*>();
	std::unordered_map<String, Font*> ResourceManager::s_Fonts = std::unordered_map<String, Font*>();
	std::unordered_map<String, Shader*> ResourceManager::s_Shaders = std::unordered_map<String, Shader*>();

	void ResourceManager::Initialise()
	{
		s_DefaultColor = LoadDefaultColor();
		s_DefaultTexture = LoadDefaultTexture();
		s_LightColor = LoadLightColor();
		s_LightTexture = LoadLightTexture();
		s_DefaultFont = LoadDefaultFont();

		s_Square = Model::Rectangle(1, 1);
		SetModel("_RESOURCE_SQUARE_", s_Square);
		s_Circle = Model::Ellipse(2, 2);
		SetModel("_RESOURCE_CIRCLE_", s_Circle);
		s_Cube = Model::Cuboid(1, 1, 1);
		SetModel("_RESOURCE_CUBE_", s_Cube);
		s_Sphere = Model::Sphere(1);
		SetModel("_RESOURCE_SPHERE_", s_Sphere);
		s_Plane = Model::Grid(1, 1, 2, 2);
		SetModel("_RESOURCE_PLANE_", s_Plane);

		Systems::Lighting().AddShader(s_LightColor);
		Systems::Lighting().AddShader(s_LightTexture);
	}

	void ResourceManager::Terminate()
	{
		s_DefaultColor->Decrement();
		s_DefaultTexture->Decrement();
		s_LightColor->Decrement();
		s_LightTexture->Decrement();
		s_DefaultFont->Decrement();
		delete s_Square;
		delete s_Circle;
		delete s_Cube;
		delete s_Sphere;
		delete s_Plane;
	}

	Shader* ResourceManager::DefaultColorShader()
	{
		return s_DefaultColor;
	}

	Shader* ResourceManager::DefaultTextureShader()
	{
		return s_DefaultTexture;
	}

	Shader* ResourceManager::LightingColorShader()
	{
		return s_LightColor;
	}

	Shader* ResourceManager::LightingTextureShader()
	{
		return s_LightTexture;
	}

	Shader* ResourceManager::DefaultFontShader()
	{
		return s_DefaultFont;
	}


	Model* ResourceManager::Square()
	{
		return s_Square;
	}

	Model* ResourceManager::Circle()
	{
		return s_Circle;
	}

	Model* ResourceManager::Cube()
	{
		return s_Cube;
	}

	Model* ResourceManager::Sphere()
	{
		return s_Sphere;
	}

	Model* ResourceManager::Plane()
	{
		return s_Plane;
	}


	Texture2D* ResourceManager::SetTexture2D(const String& name, Texture2D* texture)
	{
		AB_ASSERT(!Texture2DExists(name), "Texture with name: " + name + " already exists");
		texture->Increment();
		s_Texture2Ds[name] = texture;
		return s_Texture2Ds[name];
	}

	Model* ResourceManager::SetModel(const String& name, Model* model)
	{
		AB_ASSERT(!ModelExists(name), "Model with name: " + name + " already exists");
		model->Increment();
		s_Models[name] = model;
		return s_Models[name];
	}

	Font* ResourceManager::SetFont(const String& name, Font* font)
	{
		AB_ASSERT(!FontExists(name), "Font with name: " + name + " already exists");
		font->Increment();
		s_Fonts[name] = font;
		return s_Fonts[name];
	}

	Shader* ResourceManager::SetShader(const String& name, Shader* shader)
	{
		AB_ASSERT(!ShaderExists(name), "Shader with name: " + name + " already exists");
		shader->Increment();
		s_Shaders[name] = shader;
		return s_Shaders[name];
	}

	Texture2D* ResourceManager::GetTexture2D(const String& name)
	{
		AB_ASSERT(Texture2DExists(name), "Texture with name: " + name + " does not exist");
		return s_Texture2Ds[name];
	}

	Model* ResourceManager::GetModel(const String& name)
	{
		AB_ASSERT(ModelExists(name), "Model with name: " + name + " does not exist");
		return s_Models[name];
	}

	Font* ResourceManager::GetFont(const String& name)
	{
		AB_ASSERT(FontExists(name), "Font with name: " + name + " does not exist");
		return s_Fonts[name];
	}

	Shader* ResourceManager::GetShader(const String& name)
	{
		AB_ASSERT(ShaderExists(name), "Shader with name: " + name + " does not exist");
		return s_Shaders[name];
	}


	bool ResourceManager::ModelExists(const String& filename)
	{
		return (s_Models.find(filename) != s_Models.end());
	}

	bool ResourceManager::Texture2DExists(const String& filename)
	{
		return (s_Texture2Ds.find(filename) != s_Texture2Ds.end());
	}

	bool ResourceManager::FontExists(const String& filename)
	{
		return (s_Fonts.find(filename) != s_Fonts.end());
	}

	bool ResourceManager::ShaderExists(const String& filename)
	{
		return (s_Shaders.find(filename) != s_Shaders.end());
	}

	Shader* ResourceManager::LoadDefaultColor()
	{
		String vSource =
#include "Shaders\Source\DefaultColor_v.glsl"
			;
		String fSource =
#include "Shaders\Source\DefaultColor_f.glsl"
			;
		return new Shader(vSource, fSource);
	}

	Shader* ResourceManager::LoadDefaultTexture()
	{
		String vSource =
#include "Shaders\Source\DefaultTexture_v.glsl"
			;
		String fSource =
#include "Shaders\Source\DefaultTexture_f.glsl"
			;
		return new Shader(vSource, fSource);
	}

	Shader* ResourceManager::LoadLightColor()
	{
		String vSource =
#include "Shaders\Source\LightColor_v.glsl"
			;
		String fSource =
#include "Shaders\Source\LightColor_f.glsl"
			;
		return new Shader(vSource, fSource);
	}

	Shader* ResourceManager::LoadLightTexture()
	{
		String vSource =
#include "Shaders\Source\LightTexture_v.glsl"
			;
		String fSource =
#include "Shaders\Source\LightTexture_f.glsl"
			;
		return new Shader(vSource, fSource);
	}

	Shader* ResourceManager::LoadDefaultFont()
	{
		String vSource =
#include "Shaders\Source\DefaultFont_v.glsl"
			;
		String fSource =
#include "Shaders\Source\DefaultFont_f.glsl"
			;
		return new Shader(vSource, fSource);
	}

}