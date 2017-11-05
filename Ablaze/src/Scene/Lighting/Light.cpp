#include "Light.h"

namespace Ablaze
{

	Light::Light(const Transform& transform, LightType type, const Color& color, float intensity, const Maths::Vec3& attenuation) : Actor(transform),
		m_Type(type), m_LightColor(color), m_Intensity(intensity), m_Attenuation(attenuation)
	{ 
	
	}

	Light::Light(const Transform& transform, LightType type, const Color& color, float intensity) : Light(transform, type, color, intensity, Maths::Vec3(1.0f, 0.0f, 0.0f))
	{
	
	}

	Light::Light(const Transform& transform, LightType type, const Color& color) : Light(transform, type, color, 1.0f)
	{ 
	
	}

	Light::Light(const Transform& transform, LightType type) : Light(transform, type, Color::White())
	{ 
	
	}

	Light::Light(const Transform& transform) : Light(transform, LightType::Point)
	{ 
	
	}

	Light::Light() : Light(Transform())
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

	Light* Light::Sun(const Maths::Vec3& position)
	{
		return new Light(position, LightType::Point, Color::White(), 1.0f, Maths::Vec3(1.0f, 0.0f, 0.0f));
	}

	Light* Light::Sun(float x, float y, float z)
	{
		return Sun(Maths::Vec3(x, y, z));
	}

}