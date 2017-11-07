#pragma once
#include "Component.h"

namespace Ablaze
{

	enum class LightType
	{
		Point,
		Directional,
		Spotlight
	};

	class AB_API Light : public Component
	{
	protected:
		LightType m_Type;
		Color m_LightColor;
		float m_Intensity;
		Maths::Vec3 m_Attenuation;

	public:
		Light(LightType type, const Color& color, float intensity, const Maths::Vec3& attenuation);
		Light(LightType type, const Color& color, float intensity);
		Light(LightType type, const Color& color);
		Light(LightType type);
		Light();

		const LightType& Type() const;
		LightType& Type();
		const Color& LightColor() const;
		Color& LightColor();
		const float& Intensity() const;
		float& Intensity();
		const Maths::Vec3& Attenuation() const;
		Maths::Vec3& Attenuation();

		Component* Clone() const override;

	};

}