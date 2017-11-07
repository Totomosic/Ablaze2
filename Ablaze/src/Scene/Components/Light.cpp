#include "Light.h"

namespace Ablaze
{

	Light::Light(LightType type, const Color& color, float intensity, const Maths::Vec3& attenuation) : Component(),
		m_Type(type), m_LightColor(color), m_Intensity(intensity), m_Attenuation(attenuation)
	{ 
	
	}

	Light::Light(LightType type, const Color& color, float intensity) : Light(type, color, intensity, Maths::Vec3(1.0f, 0.0f, 0.0f))
	{
	
	}

	Light::Light(LightType type, const Color& color) : Light(type, color, 1.0f)
	{ 
	
	}

	Light::Light(LightType type) : Light(type, Color::White())
	{ 
	
	}

	Light::Light() : Light(LightType::Point)
	{
	
	}

	const LightType& Light::Type() const
	{
		return m_Type;
	}

	LightType& Light::Type()
	{
		return m_Type;
	}

	const Color& Light::LightColor() const
	{
		return m_LightColor;
	}

	Color& Light::LightColor()
	{
		return m_LightColor;
	}

	const float& Light::Intensity() const
	{
		return m_Intensity;
	}

	float& Light::Intensity()
	{
		return m_Intensity;
	}

	const Maths::Vec3& Light::Attenuation() const
	{
		return m_Attenuation;
	}

	Maths::Vec3& Light::Attenuation()
	{
		return m_Attenuation;
	}

}