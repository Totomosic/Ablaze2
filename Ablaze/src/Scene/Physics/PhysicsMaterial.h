#pragma once
#include "Common.h"

namespace Ablaze
{

	enum FrictionCombine
	{
		Average,
		Additive,
		Multiplicative
	};

	class AB_API PhysicsMaterial : public Object
	{
	private:
		static PhysicsMaterial s_Default;
		static PhysicsMaterial s_Air;
		static PhysicsMaterial s_Water;
		static PhysicsMaterial s_Grass;
		static PhysicsMaterial s_Vacuum;

	private:
		float m_StaticFriction;
		float m_KineticFriction;
		float m_Bounciness;
		FrictionCombine m_Static;
		FrictionCombine m_Kinetic;

	public:
		PhysicsMaterial(float staticFriction, float kineticFriction, float bounciness, FrictionCombine staticCombine = FrictionCombine::Average, FrictionCombine kineticCombine = FrictionCombine::Average);
		PhysicsMaterial(float staticFriction, float kineticFriction, FrictionCombine staticCombine = FrictionCombine::Average, FrictionCombine kineticCombine = FrictionCombine::Average);
		PhysicsMaterial(float bounciness, FrictionCombine staticCombine = FrictionCombine::Average, FrictionCombine kineticCombine = FrictionCombine::Average);
		PhysicsMaterial();

		float StaticFriction() const;
		float& StaticFriction();
		float KineticFriction() const;
		float& KineticFriction();
		float Bounciness() const;
		float& Bounciness();
		FrictionCombine StaticCombine() const;
		FrictionCombine& StaticCombine();
		FrictionCombine KineticCombine() const;
		FrictionCombine& KineticCombine();

		String ToString() const override;

	public:
		static PhysicsMaterial& Default();
		static PhysicsMaterial& Air();
		static PhysicsMaterial& Water();
		static PhysicsMaterial& Grass();
		static PhysicsMaterial& Vacuum();

	};

}