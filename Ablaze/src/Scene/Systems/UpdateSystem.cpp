#include "UpdateSystem.h"

namespace Ablaze
{

	void UpdateSystem::Execute()
	{
		std::vector<GameObject*> objects = GameObject::GetAll();
		std::vector<Component*> lateUpdates;
		float deltaTime = Time::DeltaTime();
		for (GameObject* object : objects)
		{
			for (Component* component : object->Components().GetAll())
			{
				if (component->Enabled())
				{
					component->Update(deltaTime);
					lateUpdates.push_back(component);
				}
			}
		}
		for (Component* component : lateUpdates)
		{
			component->LateUpdate(deltaTime);
		}
	}

}