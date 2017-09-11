#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"

namespace Ablaze
{

	struct AB_API Color : public Object
	{
		float r, g, b, a;

		Color(byte r, byte g, byte b, byte a = 255);
		Color(byte color);
		Color();

		float GetBrightness() const;
		Maths::Vec4 rgba() const;
		Maths::Vec4 abgr() const;
		Maths::Vec4 bgra() const;
		Maths::Vec3 rgb() const;
		Maths::Vec3 bgr() const;
		Maths::Vec2 rg() const;
		Maths::Vec2 gb() const;
		Maths::Vec2 rb() const;

		float* ToFloat() const;
		float* ToVertexBuffer(const long long& vertexCount) const;

		String ToString() const override;

		static Color FromFloats(float r, float g, float b, float a = 1.0f);

		static Color White();
		static Color Black();

		static Color Red();
		static Color Green();
		static Color Blue();
	
		static Color Yellow();
		static Color Cyan();
		static Color Magenta();
	};

}