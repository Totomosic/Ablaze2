#pragma once
#include "Common.h"
#include "FontFace.h"
#include "Resources\Textures\Texture2D.h"
#include "Resources\Meshes\Model.h"

namespace Ablaze
{

	class AB_API Font : public Texture2D
	{
	private:
		ftgl::texture_atlas_t* m_Atlas;
		ftgl::texture_font_t* m_Font;
		float m_Size;
		FontFace m_FontFace;

	public:
		Font(const String& filepath, float size);
		Font(const FontFace& face, float size);
		~Font();

	public:
		float FontSize() const;
		const FontFace& Face() const;
		FontFace& Face();

		float GetWidth(const String& text) const;
		float GetHeight(const String& text) const;
		Maths::Vector2f GetSize(const String& text) const;

		Model* CreateModel(const String& text, const Color& color = Color::White()) const;

		void Reload() override;

		friend class ResourceManager;

	};

}