#include "ComponentSet.h"

namespace Ablaze
{

	ComponentSet::ComponentSet(GameObject* owner) : Object(),
		m_GameObject(owner), m_Components()
	{
	
	}

	int ComponentSet::ComponentCount() const
	{
		return m_Components.size();
	}

	GameObject* ComponentSet::Owner() const
	{
		return m_GameObject;
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

	String ComponentSet::ToString() const
	{
		return "ComponentSet";
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

}