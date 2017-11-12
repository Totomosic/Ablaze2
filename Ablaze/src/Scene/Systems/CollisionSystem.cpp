#include "CollisionSystem.h"

namespace Ablaze
{

	CollisionSystem::CollisionSystem() : System()
	{
	
	}

	void CollisionSystem::Execute()
	{
		std::vector<GameObject*> dynamicObjects = GameObject::GetAllWith<Transform, BoxCollider, RigidBody>();
		std::vector<GameObject*> staticObjects = GameObject::GetAllWith<Transform, BoxCollider>();
		for (GameObject* dynamic : dynamicObjects)
		{
			Transform& dTransform = dynamic->transform();
			BoxCollider& dCollider = dynamic->GetComponent<BoxCollider>();
			RigidBody& dRigidBody = dynamic->GetComponent<RigidBody>();

			// Test for collisions against static objects
			for (GameObject* other : staticObjects)
			{
				Transform& oTransform = other->transform();
				BoxCollider& dCollider = other->GetComponent<BoxCollider>();
				// Broad phase: Sweep and prune
				// Ignore rigid body transform rotation (ie Axis aligned)
				
				// Narrow phase
			}
			// Test for collisions against other dynamic objects
			for (GameObject* other : dynamicObjects)
			{
				if (dynamic == other)
				{
					continue;
				}
				Transform& oTransform = other->transform();
				BoxCollider& dCollider = other->GetComponent<BoxCollider>();
				RigidBody& oRigidBody = other->GetComponent<RigidBody>();
				// Broad phase: Sweep and prune
				// Ignore rigid body transform rotation (ie Axis aligned)

				// Narrow phase
			}
		}
	}

}