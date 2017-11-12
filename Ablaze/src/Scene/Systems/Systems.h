#pragma once
#include "System.h"

namespace Ablaze
{

	class LightSystem;
	class PhysicsSystem;
	class CollisionSystem;

	class AB_API Systems : public Object
	{
	private:
		static std::vector<System*> s_Systems;

		static LightSystem* s_LightSystem;
		static PhysicsSystem* s_PhysicsSystem;
		static CollisionSystem* s_CollisionSystem;

	public:
		Systems() = delete;

		static void AddSystem(System* system);
		static void RemoveSystem(System* system);
		static void Run();

		static LightSystem& Lighting();
		static PhysicsSystem& Physics();
		static CollisionSystem& Collision();

		static void DisableLighting();
		static void DisablePhysics();
		static void DisableCollision();

		friend class Engine;

	private:
		static void Initialise();

	};

}