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
		Maths::Vector4f rgba() const;
		Maths::Vector4f abgr() const;
		Maths::Vector4f bgra() const;
		Maths::Vector3f rgb() const;
		Maths::Vector3f bgr() const;
		Maths::Vector2f rg() const;
		Maths::Vector2f gb() const;
		Maths::Vector2f rb() const;

		float* ToFloat() const;
		byte* ToByte() const;

		String ToString() const;
		void Serialize(JSONwriter& writer) const;

		bool operator==(const Color& other) const;
		bool operator!=(const Color& other) const;

		friend Color operator+(const Color& left, const Color& right);
		friend Color operator+(const Color& left, float right);
		friend Color operator+(float left, const Color& right);
		friend Color operator*(const Color& left, const Color& right);
		friend Color operator*(const Color& left, float right);
		friend Color operator*(float left, const Color& right);

		friend std::ostream& operator<<(std::ostream& stream, const Color& color);

	public:
		static Color FromFloats(float r, float g, float b, float a = 1.0f);
		static Color FromHSB(float hue, float saturation, float brightness); // All values range from 0 - 1
		static Color Deserialize(JSONnode& node);

		static Color Random();
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