#include "Light.h"

namespace Ablaze
{

	Light::Light(LightType type, const Color& color, float ambient, const Maths::Vec3& attenuation) : Component(),
		m_Type(type), m_LightColor(color), m_Ambient(ambient), m_Attenuation(attenuation)
	{ 
	
	}

	Light::Light(LightType type, const Color& color, float ambient) : Light(type, color, ambient, Maths::Vec3(1.0f, 0.0f, 0.0f))
	{
	
	}

	Light::Light(LightType type, const Color& color) : Light(type, color, 0.3f)
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

	const float& Light::Ambient() const
	{
		return m_Ambient;
	}

	float& Light::Ambient()
	{
		return m_Ambient;
	}

	const Maths::Vec3& Light::Attenuation() const
	{
		return m_Attenuation;
	}

	Maths::Vec3& Light::Attenuation()
	{
		return m_Attenuation;
	}

	String Light::ToString() const
	{
		return "Light";
	}

	void Light::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("Type", (int)m_Type);
		writer.WriteObject("Color", m_LightColor);
		writer.WriteAttribute("Ambient", m_Ambient);
		writer.WriteObject("Attenuation", m_Attenuation);
		writer.EndObject();
	}

	Component* Light::Clone() const
	{
		Light* light = new Light(m_Type, m_LightColor, m_Ambient, m_Attenuation);
		return light;
	}

	Component* Light::Deserialize(JSONnode& node) const
	{
		Light* l = new Light;
		l->Type() = (LightType)stoi(node["Type"].Data());
		l->LightColor() = Color::Deserialize(node["Color"]);
		l->Ambient() = stof(node["Ambient"].Data());
		l->Attenuation() = Maths::Vec3::Deserialize(node["Attenuation"]);
		return l;
	}

}