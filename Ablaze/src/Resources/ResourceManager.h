#pragma once
#include "Common.h"
#include "Asset.h"
#include "Meshes\Model.h"
#include "Meshes\Shapes.h"
#include "Textures\__Textures__.h"

namespace Ablaze
{

	class Shader;

	// Manages all resources within Engine
	class AB_API ResourceManager : public Singleton<ResourceManager>
	{
	private:
		std::shared_ptr<Shader> m_DefaultColor;
		std::shared_ptr<Shader> m_DefaultTexture;
		std::shared_ptr<Shader> m_LightColor;
		std::shared_ptr<Shader> m_LightTexture;
		std::shared_ptr<Shader> m_DefaultFont;

		// Immutable shapes that are generated once at the start and can be used indefinitely and resized/reshaped with scale on transform
		std::shared_ptr<Model> m_Square;
		std::shared_ptr<Model> m_Circle;
		std::shared_ptr<Model> m_Cube;
		std::shared_ptr<Model> m_Sphere;
		std::shared_ptr<Model> m_Plane;

	private:
		std::unordered_map<String, std::shared_ptr<Model>> m_Models;
		std::unordered_map<String, std::shared_ptr<Texture2D>> m_Texture2Ds;
		std::unordered_map<String, std::shared_ptr<Font>> m_Fonts;

	private:
		ResourceManager();

	public:
		static void Terminate();

	public:
		std::shared_ptr<Shader> LoadShader(const String& shaderFile);
		std::shared_ptr<Shader> LoadShader(const String& vFile, const String& fFile);
		std::shared_ptr<Shader> CreateShader(const String& vSource, const String& fSource);
		std::shared_ptr<Shader> CreateShader(const String& vSource, const String& gSource, const String& fSource);
		std::shared_ptr<Shader> DefaultColorShader();
		std::shared_ptr<Shader> DefaultTextureShader();
		std::shared_ptr<Shader> LightingColorShader();
		std::shared_ptr<Shader> LightingTextureShader();
		std::shared_ptr<Shader> DefaultFontShader();

		std::shared_ptr<Texture2D> LoadTexture2D(const String& textureFile, MipmapMode mipmap = MipmapMode::Enabled);
		std::shared_ptr<Texture2D> CreateBlankTexture2D(int width, int height, MipmapMode mipmap = MipmapMode::Enabled);
		std::shared_ptr<Font> LoadFont(const String& fontFile, float size);

		std::shared_ptr<Model> LoadModel(const String& objModelFile);
		std::shared_ptr<Model> LoadTextModel(const String& text, const std::shared_ptr<Font>& font, const Color& color = Color::White(), TextAlignmentH horizontal = TextAlignmentH::Center, TextAlignmentV vertical = TextAlignmentV::Center);
		std::shared_ptr<Model> CreateSquare(const Color& color = Color::White());
		std::shared_ptr<Model> CreateCircle(const Color& color = Color::White());
		std::shared_ptr<Model> CreateCube(const Color& color = Color::White());
		std::shared_ptr<Model> CreateSphere(const Color& color = Color::White());
		std::shared_ptr<Model> CreateGrid(int xVerts, int zVerts, const Color& color = Color::White());
		std::shared_ptr<Model> CreatePlane(const Color& color = Color::White());

		std::shared_ptr<Model> Square();
		std::shared_ptr<Model> Circle();
		std::shared_ptr<Model> Cube();
		std::shared_ptr<Model> Sphere();
		std::shared_ptr<Model> Plane();

		friend class Singleton<ResourceManager>;

	private:
		bool ModelExists(const String& filename);
		bool Texture2DExists(const String& filename);
		bool FontExists(const String& filename);
		std::shared_ptr<Model> AddModel(const String& filename, Model* model);
		std::shared_ptr<Texture2D> AddTexture2D(const String& filename, Texture2D* texture);
		std::shared_ptr<Font> AddFont(const String& filename, Font* font);

		void LoadDefaultColor();
		void LoadDefaultTexture();
		void LoadLightColor();
		void LoadLightTexture();
		void LoadDefaultFont();

	};

}