#include "Component.h"

namespace Ablaze
{

	std::unordered_map<String, Component*> Component::m_RegisteredComponents = std::unordered_map<String, Component*>();

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

	Component* Component::Deserialize(JSONnode& node) const
	{
		return nullptr;
	}

	void Component::Start()
	{
	
	}

	void Component::Update(double elapsedSeconds)
	{
	
	}

}