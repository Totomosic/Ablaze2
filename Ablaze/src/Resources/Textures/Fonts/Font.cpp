#include "Font.h"

namespace Ablaze
{

	Font::Font(const Filepath& filepath, float size) : Texture2D(512, 512, ImageFormat::Red, MipmapMode::Disabled),
		m_Size(size), m_FontFace({ filepath })
	{
		AB_ASSERT(filepath.Exists(), "File: " + filepath.Path() + " was not found");

		GL_CALL(glDeleteTextures(1, &m_Id));
		m_Atlas = texture_atlas_new(512, 512, 1);
		m_Font = texture_font_new_from_file(m_Atlas, size, filepath.Path().c_str());
		GL_CALL(glGenTextures(1, &m_Atlas->id));
		m_Id = m_Atlas->id;
	}

	Font::Font(const FontFace& face, float size) : Font(face.FontFile, size)
	{
	
	}

	Font::~Font()
	{
		texture_atlas_delete(m_Atlas);
		texture_font_delete(m_Font);
		Texture2D::~Texture2D();
	}

	float Font::FontSize() const
	{
		return m_Size;
	}

	const FontFace& Font::Face() const
	{
		return m_FontFace;
	}

	FontFace& Font::Face()
	{
		return m_FontFace;
	}

	float Font::GetWidth(const String& text) const
	{
		return GetSize(text).x;
	}

	float Font::GetHeight(const String& text) const
	{
		return GetSize(text).y;
	}

	Maths::Vector2f Font::GetSize(const String& text) const
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
		return Maths::Vector2f(totalLength, maxHeight);
	}

	Model* Font::CreateModel(const ColorFormattedString& string, TextAlignmentH horizontal, TextAlignmentV vertical) const
	{
		String text = string.RawString();
		if (text.length() == 0)
		{
			VertexArray* vao = new VertexArray;
			vao->CreateAttribute(0);
			vao->CreateIndexBuffer(0);
			return new Model(vao);
		}
		VertexArray* vao = new VertexArray;
		VertexBuffer* vbo = vao->CreateAttribute(text.length() * 4 * sizeof(Vertex), BufferLayout::Default());
		IndexBuffer* ibo = vao->CreateIndexBuffer(text.length() * 6 * sizeof(uint));
		Vertex* buffer = (Vertex*)vbo->Map(AccessMode::Write);
		uint* indices = new uint[text.length() * 6];
		float width = GetWidth(text);
		float height = GetHeight(text);
		float x = 0;
		float y = 0;
		if (horizontal == TextAlignmentH::Center)
		{
			x = -width / 2.0f;
		}
		else if (horizontal == TextAlignmentH::Right)
		{
			x = -width;
		}
		if (vertical == TextAlignmentV::Center)
		{
			y = -height / 2.0f;
		}
		else if (vertical == TextAlignmentV::Top)
		{
			y = -height;
		}

		int indexCount = 0;
		int indicesCount = 0;
		Color currentColor;
		for (auto& pair : string.ColorMap())
		{
			currentColor = pair.color;
			for (int i = 0; i < pair.string.length(); i++)
			{
				char c = pair.string[i];
				texture_glyph_t* glyph = texture_font_get_glyph(m_Font, c);
				if (glyph != nullptr)
				{
					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, pair.string[i - 1]);
						x += kerning;
					}

					float x0 = x + glyph->offset_x;
					float y0 = y + glyph->offset_y;
					float x1 = x0 + glyph->width;
					float y1 = y0 - glyph->height;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					buffer->position = Maths::Vector3f(x0, y0, 0);
					buffer->normal = Maths::Vector3f(0, 0, 1);
					buffer->texCoord = Maths::Vector2f(u0, v0);
					buffer->color = currentColor;
					buffer->tangent = Maths::Vector3f(0, 1, 0);
					buffer++;

					buffer->position = Maths::Vector3f(x0, y1, 0);
					buffer->normal = Maths::Vector3f(0, 0, 1);
					buffer->texCoord = Maths::Vector2f(u0, v1);
					buffer->color = currentColor;
					buffer->tangent = Maths::Vector3f(0, 1, 0);
					buffer++;

					buffer->position = Maths::Vector3f(x1, y1, 0);
					buffer->normal = Maths::Vector3f(0, 0, 1);
					buffer->texCoord = Maths::Vector2f(u1, v1);
					buffer->color = currentColor;
					buffer->tangent = Maths::Vector3f(0, 1, 0);
					buffer++;

					buffer->position = Maths::Vector3f(x1, y0, 0);
					buffer->normal = Maths::Vector3f(0, 0, 1);
					buffer->texCoord = Maths::Vector2f(u1, v0);
					buffer->color = currentColor;
					buffer->tangent = Maths::Vector3f(0, 1, 0);
					buffer++;

					x += glyph->advance_x;
					y += glyph->advance_y;

					indices[indexCount + 0] = 0 + indicesCount;
					indices[indexCount + 1] = 1 + indicesCount;
					indices[indexCount + 2] = 2 + indicesCount;
					indices[indexCount + 3] = 0 + indicesCount;
					indices[indexCount + 4] = 2 + indicesCount;
					indices[indexCount + 5] = 3 + indicesCount;

					indexCount += 6;
					indicesCount += 4;
				}
				else
				{
					AB_WARN(String("Character not found: ") + c);
				}
			}
		}
		ibo->Bind();
		ibo->Upload(indices, text.length() * 6 * sizeof(uint));
		vbo->Unmap();
		delete[] indices;

		return new Model(vao);
	}

	void Font::Reload()
	{
	
	}

}