#pragma once
#include "Scene\Components\Component.h"
#include "Resources\Textures\Fonts\Font.h"

namespace Ablaze
{

	class AB_API Text : public Component
	{
	private:
		Font* m_Font;
		ColorFormattedString m_Text;
		int m_ModelIndex;

		Maths::Vector2f m_Size;
		TextAlignmentH m_hAlign;
		TextAlignmentV m_vAlign;

	public:
		Text(const ColorFormattedString& text, Font* font, TextAlignmentH horizontal = TextAlignmentH::Center, TextAlignmentV vertical = TextAlignmentV::Center);

		Font* GetFont() const;
		const ColorFormattedString& FormattedString() const;
		String RawString() const;
		const Maths::Vector2f& Size() const;
		float Width() const;
		float Height() const;
		TextAlignmentH HorizontalAlignment() const;
		TextAlignmentV VerticalAlignment() const;

		void Start() override;

		void SetText(const ColorFormattedString& text);
		void SetFont(Font* font);
		void SetAlignment(TextAlignmentH horizontal, TextAlignmentV vertical);

		Component* Clone() const override;
		String ToString() const override;

	private:
		void UpdateModel();

	};

}