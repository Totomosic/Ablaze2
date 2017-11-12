#pragma once
#include "Common.h"
#include "Resources\Textures\Texture2D.h"

namespace Ablaze
{

	class AB_API Font : public Texture2D
	{
	private:
		ftgl::texture_atlas_t* m_Atlas;
		ftgl::texture_font_t* m_Font;
		float m_Size;

	private:
		Font(const String& filepath, float size);
		~Font();

	public:
		float Size() const;

		float GetWidth(const String& text) const;
		float GetHeight(const String& text) const;
		Maths::Vec2 GetSize(const String& text) const;

		void Reload() override;

		friend class ResourceManager;

	};

}