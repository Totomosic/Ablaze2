#include "Color.h"
#include "Utils\JSON\__JSON__.h"

namespace Ablaze
{

	Color::Color(byte r, byte g, byte b, byte a)
	{
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	}

	Color::Color(byte color) : Color(color, color, color, 255)
	{

	}

	Color::Color() : Color(255)
	{

	}

	float Color::GetBrightness() const
	{
		return (r + b + g) / 3.0f;
	}

	Maths::Vec4 Color::rgba() const
	{
		return Maths::Vec4(r, g, b, a);
	}

	Maths::Vec4 Color::abgr() const
	{
		return Maths::Vec4(a, b, g, r);
	}

	Maths::Vec4 Color::bgra() const
	{
		return Maths::Vec4(b, g, r, a);
	}

	Maths::Vec3 Color::rgb() const
	{
		return Maths::Vec3(r, g, b);
	}

	Maths::Vec3 Color::bgr() const
	{
		return Maths::Vec3(b, g, r);
	}

	Maths::Vec2 Color::rg() const
	{
		return Maths::Vec2(r, g);
	}

	Maths::Vec2 Color::gb() const
	{
		return Maths::Vec2(g, b);
	}

	Maths::Vec2 Color::rb() const
	{
		return Maths::Vec2(r, b);
	}

	String Color::ToString() const
	{
		return "Color(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
	}

	void Color::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("r", r);
		writer.WriteAttribute("g", g);
		writer.WriteAttribute("b", b);
		writer.WriteAttribute("a", a);
		writer.EndObject();
	}

	float* Color::ToFloat() const
	{
		return new float[4]{ r, g, b, a };
	}

	byte* Color::ToByte() const
	{
		return new byte[4]{ (byte)(r * 255), (byte)(g * 255), (byte)(b * 255), (byte)(a * 255) };
	}

	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		stream << color.ToString();
		return stream;
	}

	Color Color::FromFloats(float r, float g, float b, float a)
	{
		Color c((byte)(r * 255), (byte)(g * 255), (byte)(b * 255), (byte)(a * 255));
		return c;
	}

	Color Color::FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue * 360;
		float c = brightness * saturation;
		float x = c * (1 - abs(((int)h / 60) % 2 - 1));
		float m = brightness - c;

		float rd = 0;
		float gd = 0;
		float bd = 0;

		if (h < 60)
		{
			rd = c;
			gd = x;
		}
		else if (h < 120)
		{
			rd = x;
			gd = c;
		}
		else if (h < 180)
		{
			gd = c;
			bd = x;
		}
		else if (h < 240)
		{
			gd = x;
			bd = c;
		}
		else if (h < 300)
		{
			rd = x;
			bd = c;
		}
		else
		{
			rd = c;
			bd = x;
		}
		return Color((rd + m) * 255, (gd + m) * 255, (bd + m) * 255, 255);
	}

	Color Color::White()
	{
		Color c(255, 255, 255, 255);
		return c;
	}

	Color Color::Black()
	{
		Color c(0, 0, 0, 255);
		return c;
	}

	Color Color::Red()
	{
		Color c(255, 0, 0, 255);
		return c;
	}

	Color Color::Green()
	{
		Color c(0, 255, 0, 255);
		return c;
	}

	Color Color::Blue()
	{
		Color c(0, 0, 255, 255);
		return c;
	}

	Color Color::Yellow()
	{
		Color c(255, 255, 0, 255);
		return c;
	}

	Color Color::Cyan()
	{
		Color c(0, 255, 255, 255);
		return c;
	}

	Color Color::Magenta()
	{
		Color c(255, 0, 255, 255);
		return c;
	}

	Color Color::CornflowerBlue()
	{
		Color c(100, 200, 255, 255);
		return c;
	}

}