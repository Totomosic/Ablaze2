#include "ComponentSet.h"
#include "Components\__Components__.h"

namespace Ablaze
{

	ComponentSet::ComponentSet(GameObject* owner) : Object(),
		m_GameObject(owner), m_Components()
	{
	
	}

	ComponentSet::~ComponentSet()
	{
		for (auto pair : m_Components)
		{
			delete pair.second;
		}
	}

	int ComponentSet::ComponentCount() const
	{
		return m_Components.size();
	}

	GameObject* ComponentSet::Owner() const
	{
		return m_GameObject;
	}

	std::vector<Component*> ComponentSet::GetAll() const
	{
		std::vector<Component*> components;
		for (auto pair : m_Components)
		{
			components.push_back(pair.second);
		}
		return components;
	}

	const std::unordered_map<std::type_index, Component*>& ComponentSet::GetComponentMap() const
	{
		return m_Components;
	}

	Component* ComponentSet::GetComponent(const std::type_index& type) const
	{
		if (!HasComponent(type))
		{
			return nullptr;
		}
		return m_Components.at(type);
	}

	bool ComponentSet::HasComponent(const std::type_index& type) const
	{
		return HasComponentType(type);
	}

	void ComponentSet::RemoveComponent(Component* component, float delay)
	{
		for (auto& pair : m_Components)
		{
			if (pair.second == component)
			{
				m_GameObject->DestroyComponent(component, delay);
				return;
			}
		}
		AB_ASSERT(false, "GameObject did not have this component");
	}

	void ComponentSet::RemoveComponent(const std::type_index& component, float delay)
	{
		AB_ASSERT(HasComponent(component), "GameObject does not have a component of type: " + String(component.name()));
		Component* c = m_Components[component];
		c->Disable();
		m_GameObject->DestroyComponent(c, delay);
	}

	String ComponentSet::ToString() const
	{
		return "ComponentSet";
	}

	void ComponentSet::Serialize(JSONwriter& writer) const
	{

	}

	void ComponentSet::AddComponent(const std::type_index& type, Component* component)
	{
		if (HasComponent(type))
		{
			delete m_Components[type];
		}
		m_Components[type] = component;
		component->m_GameObject = m_GameObject;
		component->Start();
	}

	bool ComponentSet::HasComponentType(const std::type_index& type) const
	{
		return m_Components.find(type) != m_Components.end();
	}

	void ComponentSet::DeleteComponent(Component* component)
	{
		for (auto& pair : m_Components)
		{
			if (pair.second == component)
			{
				m_Components.erase(pair.first);
				delete component;
				return;
			}
		}
	}

}