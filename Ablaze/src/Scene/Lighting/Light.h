#pragma once
#include "Scene\Actor.h"

namespace Ablaze
{

	enum class LightType
	{
		Point,
		Directional,
		Spotlight
	};

	class AB_API Light : public Actor
	{
	protected:
		LightType m_Type;
		Color m_LightColor;
		float m_Intensity;
		Maths::Vec3 m_Attenuation;

	public:
		Light(const Transform& transform, LightType type, const Color& color, float intensity, const Maths::Vec3& attenuation);
		Light(const Transform& transform, LightType type, const Color& color, float intensity);
		Light(const Transform& transform, LightType type, const Color& color);
		Light(const Transform& transform, LightType type);
		Light(const Transform& transform);
		Light();

		const LightType& Type() const;
		LightType& Type();
		const Color& LightColor() const;
		Color& LightColor();
		const float& Intensity() const;
		float& Intensity();
		const Maths::Vec3& Attenuation() const;
		Maths::Vec3& Attenuation();

		friend class Layer;

	public:
		static Light* Sun(const Maths::Vec3& position);
		static Light* Sun(float x, float y, float z);

	};

}