#include "UpdateSystem.h"

namespace Ablaze
{

	void UpdateSystem::Execute()
	{
		std::vector<GameObject*> objects = GameObject::GetAll();
		for (GameObject* object : objects)
		{
			for (Component* component : object->Components().GetAll())
			{
				if (component->Enabled())
				{
					component->Update(Time::DeltaTime());
				}
			}
		}
	}

}