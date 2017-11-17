#pragma once
#include "System.h"

namespace Ablaze
{

	class UpdateSystem;
	class LightSystem;
	class PhysicsSystem;
	class CollisionSystem;

	class AB_API Systems : public Object
	{
	private:
		static std::vector<System*> s_Systems;

		static UpdateSystem* s_UpdateSystem;
		static LightSystem* s_LightSystem;
		static PhysicsSystem* s_PhysicsSystem;
		static CollisionSystem* s_CollisionSystem;

	public:
		Systems() = delete;

		static void AddSystem(System* system);
		static void RemoveSystem(System* system);
		static void Run();

		static UpdateSystem& Updating();
		static LightSystem& Lighting();
		static PhysicsSystem& Physics();
		static CollisionSystem& Collision();

		static void DisableUpdate();
		static void DisableLighting();
		static void DisablePhysics();
		static void DisableCollision();

		friend class Engine;

	private:
		static void Initialise();

	};

}