#include "Systems.h"
#include "LightSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"

namespace Ablaze
{

	std::vector<System*> Systems::s_Systems = std::vector<System*>();

	LightSystem* Systems::s_LightSystem = new LightSystem();
	PhysicsSystem* Systems::s_PhysicsSystem = new PhysicsSystem();
	CollisionSystem* Systems::s_CollisionSystem = new CollisionSystem();

	void Systems::AddSystem(System* system)
	{
		s_Systems.push_back(system);
	}
	
	void Systems::RemoveSystem(System* system)
	{
		auto it = std::find(s_Systems.begin(), s_Systems.end(), system);
		s_Systems.erase(it);
	}

	void Systems::Run()
	{
		for (System* system : s_Systems)
		{
			system->Execute();
		}
	}

	LightSystem& Systems::Lighting()
	{
		return *s_LightSystem;
	}

	PhysicsSystem& Systems::Physics()
	{
		return *s_PhysicsSystem;
	}

	CollisionSystem& Systems::Collision()
	{
		return *s_CollisionSystem;
	}

	void Systems::DisableLighting()
	{
		RemoveSystem(s_LightSystem);
	}

	void Systems::DisablePhysics()
	{
		RemoveSystem(s_PhysicsSystem);
	}

	void Systems::DisableCollision()
	{
		RemoveSystem(s_CollisionSystem);
	}

	void Systems::Initialise()
	{
		AddSystem(s_LightSystem);
		AddSystem(s_PhysicsSystem);
		AddSystem(s_CollisionSystem);
	}

}