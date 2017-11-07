#include "GameObject.h"
#include "SceneManager.h"
#include "ComponentSet.h"

namespace Ablaze
{

	GameObject::GameObject() : Object(),
		m_Components(new ComponentSet(this)), m_Id(0), m_Layer(nullptr)
	{
		
	}

	GameObject::~GameObject()
	{
		m_Layer->m_GameObjects[m_Id] = nullptr;
	}
	
	const ComponentSet& GameObject::Components() const
	{
		return *m_Components;
	}

	ComponentSet& GameObject::Components()
	{
		return *m_Components;
	}

	String GameObject::ToString() const
	{
		return "GameObject";
	}

}