#include "Color.h"

namespace Ablaze
{

	Color::Color(byte r, byte g, byte b, byte a)
	{
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	}

	Color::Color(byte color) : Color(color, color, color, color)
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

	float* Color::ToFloat() const
	{
		return new float[4]{ r, g, b, a };
	}

	float* Color::ToVertexBuffer(const long long& vertexCount) const
	{
		float* values = new float[4 * vertexCount];
		float* color = ToFloat();

		for (int i = 0; i < vertexCount; i++)
		{
			values[i * 4 + 0] = color[0];
			values[i * 4 + 1] = color[1];
			values[i * 4 + 2] = color[2];
			values[i * 4 + 3] = color[3];
		}

		delete[] color;
		return values;
	}

	Color Color::FromFloats(float r, float g, float b, float a)
	{
		Color c((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(a * 255));
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

}