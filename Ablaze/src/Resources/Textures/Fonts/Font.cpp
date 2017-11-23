#include "Font.h"

namespace Ablaze
{

	Font::Font(const String& filepath, float size) : Texture2D(512, 512, ImageFormat::Red, MipmapMode::Disabled),
		m_Size(size)
	{
		m_Atlas = texture_atlas_new(512, 512, 1);
		m_Font = texture_font_new_from_file(m_Atlas, size, filepath.c_str());
		glGenTextures(1, &m_Atlas->id);
		m_Id = m_Atlas->id;
	}

	Font::~Font()
	{
		delete m_Atlas;
		delete m_Font;
		Texture2D::~Texture2D();
	}

	float Font::Size() const
	{
		return m_Size;
	}

	float Font::GetWidth(const String& text) const
	{
		return GetSize(text).x;
	}

	float Font::GetHeight(const String& text) const
	{
		return GetSize(text).y;
	}

	Maths::Vec2 Font::GetSize(const String& text) const
	{
		float totalLength = 0;
		float maxHeight = 0;
		for (int i = 0; i < text.length(); i++)
		{
			char c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(m_Font, c);
			if (glyph != nullptr)
			{
				maxHeight = (glyph->height > maxHeight) ? glyph->height : maxHeight;
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
					totalLength += kerning;
				}
				totalLength += glyph->advance_x;
			}
		}
		return Maths::Vec2(totalLength, maxHeight);
	}

	void Font::Reload()
	{
	
	}

}