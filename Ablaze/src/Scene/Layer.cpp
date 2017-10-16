#include "Layer.h"

namespace Ablaze
{

	Layer::Layer(const String& name, Camera* camera) : Object(),
		m_Name(name), m_Camera(camera)
	{
	
	}

	Layer::Layer(const String& name) : Layer(name, nullptr)
	{
	
	}

	Layer::~Layer()
	{
		for (Entity* entity : m_Entities)
		{
			delete entity;
		}
		delete m_Camera; // Could delete nullptr
	}

	const String& Layer::GetName() const
	{
		return m_Name;
	}

	const std::vector<Entity*>& Layer::GetEntities() const
	{
		return m_Entities;
	}

	Camera* Layer::GetCamera() const
	{
		return m_Camera;
	}

	bool Layer::HasCamera() const
	{
		return m_Camera != nullptr;
	}

	int Layer::EntityCount() const
	{
		return m_Entities.size();
	}

	void Layer::SetCamera(Camera* camera)
	{
		m_Camera = camera;
	}

	void Layer::AddEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void Layer::RemoveEntity(Entity* entity)
	{
		auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);
		m_Entities.erase(it);
	}

	void Layer::RemoveEntity(int index)
	{
		m_Entities.erase(m_Entities.begin() + index);
	}

	void Layer::Clear()
	{
		m_Entities.clear();
	}

	String Layer::ToString() const
	{
		return "Layer";
	}

}