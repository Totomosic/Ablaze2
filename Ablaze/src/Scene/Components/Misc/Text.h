#pragma once
#include "Scene\Components\Component.h"
#include "Resources\Textures\Fonts\Font.h"

namespace Ablaze
{

	class AB_API Text : public Component
	{
	private:
		Font* m_Font;
		Color m_Color;
		String m_Text;
		int m_ModelIndex;

		Maths::Vector2f m_Size;
		TextAlignmentH m_hAlign;
		TextAlignmentV m_vAlign;

	public:
		Text(const String& text, Font* font, const Color& color = Color::Black(), TextAlignmentH horizontal = TextAlignmentH::Center, TextAlignmentV vertical = TextAlignmentV::Center);

		Font* GetFont() const;
		const Color& FontColor() const;
		const String& RawString() const;
		const Maths::Vector2f& Size() const;
		float Width() const;
		float Height() const;
		TextAlignmentH HorizontalAlignment() const;
		TextAlignmentV VerticalAlignment() const;

		void Start() override;

		void SetText(const String& text);
		void SetFont(Font* font);
		void SetColor(const Color& color);
		void SetAlignment(TextAlignmentH horizontal, TextAlignmentV vertical);

		Component* Clone() const override;
		String ToString() const override;

	private:
		void UpdateModel();

	};

}