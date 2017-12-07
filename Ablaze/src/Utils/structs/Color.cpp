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

	Maths::Vector4f Color::rgba() const
	{
		return Maths::Vector4f(r, g, b, a);
	}

	Maths::Vector4f Color::abgr() const
	{
		return Maths::Vector4f(a, b, g, r);
	}

	Maths::Vector4f Color::bgra() const
	{
		return Maths::Vector4f(b, g, r, a);
	}

	Maths::Vector3f Color::rgb() const
	{
		return Maths::Vector3f(r, g, b);
	}

	Maths::Vector3f Color::bgr() const
	{
		return Maths::Vector3f(b, g, r);
	}

	Maths::Vector2f Color::rg() const
	{
		return Maths::Vector2f(r, g);
	}

	Maths::Vector2f Color::gb() const
	{
		return Maths::Vector2f(g, b);
	}

	Maths::Vector2f Color::rb() const
	{
		return Maths::Vector2f(r, b);
	}

	String Color::ToString() const
	{
		return "Color(" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + ";" + std::to_string(a) + ")";
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

	Color Color::Deserialize(JSONnode& node)
	{
		Color c;
		c.r = stof(node["r"].Data());
		c.g = stof(node["g"].Data());
		c.b = stof(node["b"].Data());
		c.a = stof(node["a"].Data());
		return c;
	}

	Color Color::Random()
	{
		Color c = Color::FromFloats(Random::NextFloat(0.0f, 1.0f), Random::NextFloat(0.0f, 1.0f), Random::NextFloat(0.0f, 1.0f), 1.0f);
		return c;
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