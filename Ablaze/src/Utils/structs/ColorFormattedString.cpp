#include "ColorFormattedString.h"
#include "Utils\Functions.h"

namespace Ablaze
{

	ColorFormattedString::ColorFormattedString(const String& string) : Object()
	{
		m_Colors = Encode(string);
	}

	ColorFormattedString::ColorFormattedString(const char* string) : ColorFormattedString(String(string))
	{
		
	}

	ColorFormattedString::ColorFormattedString(const std::vector<ColoredString>& colorMapping)
	{
		m_Colors = colorMapping;
	}

	ColorFormattedString::ColorFormattedString() : ColorFormattedString("")
	{
	
	}

	const std::vector<ColoredString>& ColorFormattedString::ColorMap() const
	{
		return m_Colors;
	}

	String ColorFormattedString::RawString() const
	{
		String s;
		for (const auto& pair : m_Colors)
		{
			s += pair.string;
		}
		return s;
	}

	String ColorFormattedString::ToString() const
	{
		return RawString();
	}

	std::vector<ColoredString> ColorFormattedString::Encode(const String& string) const
	{
		if (!ContainsFormatting(string))
		{
			return { {string, Color::White()} };
		}
		std::vector<ColoredString> mapping;
		std::vector<String> parts = SplitString(string, "<<");
		for (String& s : parts)
		{
			std::vector<String> colorString = SplitString(s, ">>");
			AB_ASSERT(colorString.size() == 2, "Formatting Error");
			String& color = colorString[0];
			String& string = colorString[1];
			std::vector<String> colorComps = SplitString(color, ",");
			Color c;
			if (colorComps.size() == 4)
			{
				c = Color(std::stoi(colorComps[0]), std::stoi(colorComps[1]), std::stoi(colorComps[2]), std::stoi(colorComps[3]));
			}
			else
			{
				c = Color(std::stoi(colorComps[0]), std::stoi(colorComps[1]), std::stoi(colorComps[2]));
			}
			mapping.push_back({ string, c });
		}
		return mapping;
	}

	String ColorFormattedString::Decode(const std::vector<ColoredString>& colorMapping) const
	{
		return "";
	}

	bool ColorFormattedString::ContainsFormatting(const String& string) const
	{
		return (string.find("<<") != String::npos) && (string.find(">>") != String::npos);
	}

}