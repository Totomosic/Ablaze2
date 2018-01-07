#pragma once
#include "Object.h"
#include "Color.h"

namespace Ablaze
{

	struct AB_API ColoredString
	{
	public:
		String string;
		Color color;
	};

	class AB_API ColorFormattedString : public Object
	{
	private:
		std::vector<ColoredString> m_Colors;

	public:
		ColorFormattedString(const String& string);
		ColorFormattedString(const char* string);
		ColorFormattedString(const std::vector<ColoredString>& colorMapping);
		ColorFormattedString();

		const std::vector<ColoredString>& ColorMap() const;
		String RawString() const;
		String ToString() const override;

	private:
		std::vector<ColoredString> Encode(const String& string) const;
		String Decode(const std::vector<ColoredString>& colorMapping) const;
		bool ContainsFormatting(const String& string) const;

	};

}

/*
	Formatted String:
	<<255,255,255>>Hi<<255,0,0>> there
*/