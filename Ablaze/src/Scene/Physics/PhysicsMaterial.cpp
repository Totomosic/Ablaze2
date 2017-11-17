#include "PhysicsMaterial.h"

namespace Ablaze
{

	PhysicsMaterial PhysicsMaterial::s_Default = PhysicsMaterial();
	PhysicsMaterial PhysicsMaterial::s_Air = PhysicsMaterial(0.0f, 0.01f, 0.0f);
	PhysicsMaterial PhysicsMaterial::s_Water = PhysicsMaterial(0.1f, 0.1f, 0.0f);
	PhysicsMaterial PhysicsMaterial::s_Grass = PhysicsMaterial(0.3f, 0.4f, 0.1f);
	PhysicsMaterial PhysicsMaterial::s_Vacuum = PhysicsMaterial(0.0f, 0.0f, 0.0f);

	PhysicsMaterial::PhysicsMaterial(float staticFriction, float kineticFriction, float bounciness, FrictionCombine staticCombine, FrictionCombine kineticCombine) : Object(),
		m_StaticFriction(staticFriction), m_KineticFriction(kineticFriction), m_Bounciness(bounciness), m_Static(staticCombine), m_Kinetic(kineticCombine)
	{
	
	}

	PhysicsMaterial::PhysicsMaterial(float staticFriction, float kineticFriction, FrictionCombine staticCombine, FrictionCombine kineticCombine) : PhysicsMaterial(staticFriction, kineticFriction, 0.0f, staticCombine, kineticCombine)
	{
	
	}

	PhysicsMaterial::PhysicsMaterial(float bounciness, FrictionCombine staticCombine, FrictionCombine kineticCombine) : PhysicsMaterial(0.0f, 0.0f, bounciness, staticCombine, kineticCombine)
	{
	
	}

	PhysicsMaterial::PhysicsMaterial() : PhysicsMaterial(0.0f, 0.0f)
	{
	
	}

	float PhysicsMaterial::StaticFriction() const
	{
		return m_StaticFriction;
	}

	float& PhysicsMaterial::StaticFriction()
	{
		return m_StaticFriction;
	}

	float PhysicsMaterial::KineticFriction() const
	{
		return m_KineticFriction;
	}

	float& PhysicsMaterial::KineticFriction()
	{
		return m_KineticFriction;
	}

	float PhysicsMaterial::Bounciness() const
	{
		return m_Bounciness;
	}

	float& PhysicsMaterial::Bounciness()
	{
		return m_Bounciness;
	}

	FrictionCombine PhysicsMaterial::StaticCombine() const
	{
		return m_Static;
	}

	FrictionCombine& PhysicsMaterial::StaticCombine()
	{
		return m_Static;
	}

	FrictionCombine PhysicsMaterial::KineticCombine() const
	{
		return m_Kinetic;
	}

	FrictionCombine& PhysicsMaterial::KineticCombine()
	{
		return m_Kinetic;
	}

	String PhysicsMaterial::ToString() const
	{
		return "PhysicsMaterial";
	}

	PhysicsMaterial& PhysicsMaterial::Default()
	{
		return s_Default;
	}

	PhysicsMaterial& PhysicsMaterial::Air()
	{
		return s_Air;
	}

	PhysicsMaterial& PhysicsMaterial::Water()
	{
		return s_Water;
	}

	PhysicsMaterial& PhysicsMaterial::Grass()
	{
		return s_Grass;
	}

	PhysicsMaterial& PhysicsMaterial::Vacuum()
	{
		return s_Vacuum;
	}

}