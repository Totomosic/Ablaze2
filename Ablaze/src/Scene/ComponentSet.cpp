#include "ComponentSet.h"
#include "Components\__Components__.h"

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

	String ComponentSet::ToString() const
	{
		return "ComponentSet";
	}

	void ComponentSet::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		for (auto pair : m_Components)
		{
			writer.WriteObject(CleanJSONString(pair.first.name()), *pair.second);
		}
		writer.EndObject();
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

	ComponentSet* ComponentSet::Deserialize(JSONnode& node, GameObject* owner)
	{
		ComponentSet* set = new ComponentSet(owner);
		for (int i = 0; i < node.ChildCount(); i++)
		{
			set->AddComponent(Component::m_RegisteredComponents[node[i].Key()]->Deserialize(node[i]));
		}
		return set;
	}

}