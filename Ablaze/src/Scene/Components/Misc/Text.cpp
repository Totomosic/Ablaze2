#include "Text.h"
#include "Scene\Components\MeshRenderer.h"
#include "Resources\ResourceManager.h"

namespace Ablaze
{

	Text::Text(const ColorFormattedString& text, Font* font, TextAlignmentH horizontal, TextAlignmentV vertical) : Component(),
		m_Font(font), m_Text(text), m_ModelIndex(-1), m_hAlign(horizontal), m_vAlign(vertical)
	{
	
	}

	Font* Text::GetFont() const
	{
		return m_Font;
	}

	const ColorFormattedString& Text::FormattedString() const
	{
		return m_Text;
	}

	String Text::RawString() const
	{
		return m_Text.RawString();
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
		if (m_GameObject->HasComponent<MeshRenderer>())
		{
			m_ModelIndex = m_GameObject->mesh().MeshCount();
			m_GameObject->mesh().AddMesh(new Mesh(m_Font->CreateModel(m_Text, m_hAlign, m_vAlign), Material(Color::White(), ResourceManager::DefaultFontShader(), "Tex0", m_Font)));
		}
		else
		{
			m_GameObject->AddComponent(new MeshRenderer(new Mesh(m_Font->CreateModel(m_Text, m_hAlign, m_vAlign), Material(Color::White(), ResourceManager::DefaultFontShader(), "Tex0", m_Font))));
			m_ModelIndex = 0;
		}
		m_GameObject->mesh().GetMesh(m_ModelIndex)->GetMaterial().RenderSettings().DepthFunc = DepthFunction::Lequal;
		m_Size = m_Font->GetSize(m_Text.RawString());
	}

	void Text::SetText(const ColorFormattedString& text)
	{
		m_Text = text;
		UpdateModel();
	}

	void Text::SetFont(Font* font)
	{
		m_Font = font;
		UpdateModel();
	}

	void Text::SetAlignment(TextAlignmentH horizontal, TextAlignmentV vertical)
	{
		m_hAlign = horizontal;
		m_vAlign = vertical;
		UpdateModel();
	}

	Component* Text::Clone() const
	{
		Text* t = new Text(m_Text, m_Font, m_hAlign, m_vAlign);
		t->m_ModelIndex = m_ModelIndex;
		return t;
	}

	String Text::ToString() const
	{
		return "Text";
	}

	void Text::UpdateModel()
	{
		m_GameObject->mesh().GetMesh(m_ModelIndex)->SetModel(m_Font->CreateModel(m_Text, m_hAlign, m_vAlign));
		m_Size = m_Font->GetSize(m_Text.RawString());
	}

}