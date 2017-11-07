#include "Component.h"

namespace Ablaze
{

	Component::Component() : Object(),
		m_GameObject(nullptr)
	{
		
	}

	Component::~Component()
	{
	
	}

	GameObject* Component::Owner() const
	{
		return m_GameObject;
	}

	void Component::Start()
	{
	
	}

	void Component::Update(double elapsedSeconds)
	{
	
	}

}