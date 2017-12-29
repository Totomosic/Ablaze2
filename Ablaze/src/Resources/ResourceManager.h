#pragma once
#include "Common.h"
#include "Asset.h"
#include "Meshes\Mesh.h"
#include "Meshes\Shapes.h"
#include "Textures\Texture2D.h"
#include "Textures\Fonts\__Fonts__.h"

namespace Ablaze
{

	class Shader;

	// Manages all resources within Engine
	class AB_API ResourceManager
	{
	private:
		static Shader* s_DefaultColor;
		static Shader* s_DefaultTexture;
		static Shader* s_LightColor;
		static Shader* s_LightTexture;
		static Shader* s_DefaultFont;

		// Immutable shapes that are generated once at the start and can be used indefinitely and resized/reshaped with scale on transform
		static Model* s_Square;
		static Model* s_Circle;
		static Model* s_Cube;
		static Model* s_Sphere;
		static Model* s_Plane;

	private:
		static std::unordered_map<String, Model*> s_Models;
		static std::unordered_map<String, Texture2D*> s_Texture2Ds;
		static std::unordered_map<String, Font*> s_Fonts;
		static std::unordered_map<String, Shader*> s_Shaders;

	private:
		ResourceManager() = delete;

	public:
		static void Initialise();
		static void Terminate();

	public:
		static Shader* DefaultColorShader();
		static Shader* DefaultTextureShader();
		static Shader* LightingColorShader();
		static Shader* LightingTextureShader();
		static Shader* DefaultFontShader();

		static Model* Square();
		static Model* Circle();
		static Model* Cube();
		static Model* Sphere();
		static Model* Plane();

		static Texture2D* SetTexture2D(const String& name, Texture2D* texture);
		static Model* SetModel(const String& name, Model* model);
		static Font* SetFont(const String& name, Font* font);
		static Shader* SetShader(const String& name, Shader* shader);
		static Texture2D* GetTexture2D(const String& name);
		static Model* GetModel(const String& name);
		static Font* GetFont(const String& name);
		static Shader* GetShader(const String& name);

	private:
		static bool ModelExists(const String& filename);
		static bool Texture2DExists(const String& filename);
		static bool FontExists(const String& filename);
		static bool ShaderExists(const String& filename);

		static Shader* LoadDefaultColor();
		static Shader* LoadDefaultTexture();
		static Shader* LoadLightColor();
		static Shader* LoadLightTexture();
		static Shader* LoadDefaultFont();

	};

}