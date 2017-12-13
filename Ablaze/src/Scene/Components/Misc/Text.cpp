#include "Text.h"
#include "Scene\Components\Mesh.h"

namespace Ablaze
{

	Text::Text(const String& text, const std::shared_ptr<Font>& font, const Color& color, TextAlignmentH horizontal, TextAlignmentV vertical) : Component(),
		m_Font(font), m_Color(color), m_Text(text), m_ModelIndex(-1), m_hAlign(horizontal), m_vAlign(vertical)
	{
	
	}

	const std::shared_ptr<Font>& Text::GetFont() const
	{
		return m_Font;
	}

	const Color& Text::FontColor() const
	{
		return m_Color;
	}

	const String& Text::RawString() const
	{
		return m_Text;
	}

	const Maths::Vector2f& Text::Size() const
	{
		return m_Size;
	}

	float Text::Width() const
	{
		return Size().x;
	}

	float Text::Height() const
	{
		return Size().y;
	}

	TextAlignmentH Text::HorizontalAlignment() const
	{
		return m_hAlign;
	}

	TextAlignmentV Text::VerticalAlignment() const
	{
		return m_vAlign;
	}

	void Text::Start()
	{
		if (m_GameObject->HasComponent<Mesh>())
		{
			m_ModelIndex = m_GameObject->mesh().ModelCount();
			m_GameObject->mesh().AddModel(ResourceManager::Instance().LoadTextModel(m_Text, m_Font, Color::White(), m_hAlign, m_vAlign), std::make_shared<Material<Font>>(m_Color, ResourceManager::Instance().DefaultFontShader(), "Tex0", m_Font));
		}
		else
		{
			m_GameObject->AddComponent(new Mesh(ResourceManager::Instance().LoadTextModel(m_Text, m_Font, Color::White(), m_hAlign, m_vAlign), std::make_shared<Material<Font>>(m_Color, ResourceManager::Instance().DefaultFontShader(), "Tex0", m_Font)));
			m_ModelIndex = 0;
		}
		m_GameObject->mesh().GetMaterial(m_ModelIndex)->RenderSettings().UseDepthTest = false;
		m_Size = m_Font->GetSize(m_Text);
	}

	void Text::SetText(const String& text)
	{
		m_Text = text;
		UpdateModel();
	}

	void Text::SetFont(const std::shared_ptr<Font>& font)
	{
		m_Font = font;
		UpdateModel();
	}

	void Text::SetColor(const Color& color)
	{
		m_Color = color;
		m_GameObject->mesh().GetMaterial(m_ModelIndex)->BaseColor() = m_Color;
	}

	void Text::SetAlignment(TextAlignmentH horizontal, TextAlignmentV vertical)
	{
		m_hAlign = horizontal;
		m_vAlign = vertical;
		UpdateModel();
	}

	Component* Text::Clone() const
	{
		Text* t = new Text(m_Text, m_Font, m_Color, m_hAlign, m_vAlign);
		t->m_ModelIndex = m_ModelIndex;
		return t;
	}

	String Text::ToString() const
	{
		return "Text";
	}

	void Text::UpdateModel()
	{
		m_GameObject->mesh().GetModel(m_ModelIndex) = ResourceManager::Instance().LoadTextModel(m_Text, m_Font, Color::White(), m_hAlign, m_vAlign);
		m_Size = m_Font->GetSize(m_Text);
	}

}