#include "Component.h"

namespace Ablaze
{

	Component::Component() : Object(),
		m_GameObject(nullptr), m_Enabled(true)
	{
		
	}

	Component::~Component()
	{
	
	}

	GameObject* Component::Owner() const
	{
		return m_GameObject;
	}

	const bool Component::Enabled() const
	{
		return m_Enabled;
	}

	bool& Component::Enabled()
	{
		return m_Enabled;
	}

	void Component::Enable()
	{
		m_Enabled = true;
	}

	void Component::Disable()
	{
		m_Enabled = false;
	}

	void Component::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.EndObject();
	}

	void Component::Start()
	{
	
	}

	void Component::Update(double elapsedSeconds)
	{
	
	}

}