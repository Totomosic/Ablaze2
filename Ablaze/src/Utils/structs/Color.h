#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"

namespace Ablaze
{

	class JSONwriter;
	class JSONnode;

	struct AB_API Color
	{
	public:
		float r;
		float g;
		float b;
		float a;

	public:
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
		byte* ToByte() const;

		String ToString() const;
		void Serialize(JSONwriter& writer) const;

		friend std::ostream& operator<<(std::ostream& stream, const Color& color);

	public:
		static Color FromFloats(float r, float g, float b, float a = 1.0f);
		static Color FromHSB(float hue, float saturation, float brightness); // All values range from 0 - 1
		static Color Deserialize(JSONnode& node);

		static Color White();
		static Color Black();

		static Color Red();
		static Color Green();
		static Color Blue();
	
		static Color Yellow();
		static Color Cyan();
		static Color Magenta();

		static Color CornflowerBlue();

	};

}