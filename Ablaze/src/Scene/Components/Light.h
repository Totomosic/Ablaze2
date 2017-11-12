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
		float m_Ambient;
		Maths::Vec3 m_Attenuation;

	public:
		Light(LightType type, const Color& color, float ambient, const Maths::Vec3& attenuation);
		Light(LightType type, const Color& color, float ambient);
		Light(LightType type, const Color& color);
		Light(LightType type);
		Light();

		const LightType& Type() const;
		LightType& Type();
		const Color& LightColor() const;
		Color& LightColor();
		const float& Ambient() const;
		float& Ambient();
		const Maths::Vec3& Attenuation() const;
		Maths::Vec3& Attenuation();

		String ToString() const override;
		Component* Clone() const override;

	};

}