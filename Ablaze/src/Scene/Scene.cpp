#include "Scene.h"

namespace Ablaze
{

	Scene::Scene() : Object()
	{
	
	}

	Scene::~Scene()
	{
		for (auto ent : m_Entities)
		{
			delete ent;
		}
		for (auto cam : m_Cameras)
		{
			delete cam;
		}
	}

	const std::vector<Entity*>& Scene::GetEntities() const
	{
		return m_Entities;
	}

	const std::vector<Camera*>& Scene::GetCameras() const
	{
		return m_Cameras;
	}

	int Scene::EntityCount() const
	{
		return m_Entities.size();
	}

	int Scene::CameraCount() const
	{
		return m_Cameras.size();
	}

	void Scene::AddEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void Scene::AddCamera(Camera* camera)
	{
		m_Cameras.push_back(camera);
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);
		m_Entities.erase(it);
	}

	void Scene::RemoveEntity(int index)
	{
		m_Entities.erase(m_Entities.begin() + index);
	}

	void Scene::RemoveCamera(Camera* camera)
	{
		auto it = std::find(m_Cameras.begin(), m_Cameras.end(), camera);
		m_Cameras.erase(it);
	}

	void Scene::RemoveCamera(int index)
	{
		m_Cameras.erase(m_Cameras.begin() + index);
	}

	void Scene::ClearEntities()
	{
		for (auto ent : m_Entities)
		{
			delete ent;
		}
		m_Entities.clear();
	}

	void Scene::ClearCameras()
	{
		for (auto cam : m_Cameras)
		{
			delete cam;
		}
		m_Cameras.clear();
	}

	const Entity& Scene::GetEntity(int index) const
	{
		return *m_Entities[index];
	}

	Entity& Scene::GetEntity(int index)
	{
		return *m_Entities[index];
	}

	const Camera& Scene::GetCamera(int index) const
	{
		return *m_Cameras[index];
	}

	Camera& Scene::GetCamera(int index)
	{
		return *m_Cameras[index];
	}

	String Scene::ToString() const
	{
		return "Scene";
	}

}