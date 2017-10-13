#include "Scene.h"

namespace Ablaze
{

	Scene::Scene() : Object()
	{
		m_CurrentLayer = nullptr;
	}

	Scene::Scene(const String& layerName, Camera* layerCamera) : Scene()
	{
		CreateLayer(layerName, layerCamera);
	}

	Scene::~Scene()
	{
		for (Layer* layer : m_LayerOrder)
		{
			delete layer;
		}
	}

	bool Scene::HasLayer() const
	{
		return m_CurrentLayer != nullptr;
	}

	const Layer& Scene::CurrentLayer() const
	{
		return *m_CurrentLayer;
	}

	Layer& Scene::CurrentLayer()
	{
		return *m_CurrentLayer;
	}

	const Layer& Scene::GetLayer(const String& name) const
	{
		return *m_Layers.at(name);
	}

	const Layer& Scene::GetLayer(int index) const
	{
		return *m_LayerOrder[index];
	}

	Layer& Scene::GetLayer(const String& name)
	{
		return *m_Layers.at(name);
	}

	Layer& Scene::GetLayer(int index)
	{
		return *m_LayerOrder[index];
	}

	const std::vector<Layer*>& Scene::GetLayers() const
	{
		return m_LayerOrder;
	}

	void Scene::CreateLayer(const String& name, Camera* camera)
	{
		Layer* layer = new Layer(name, camera);
		m_Layers[name] = layer;
		m_LayerOrder.push_back(layer);
		if (m_CurrentLayer == nullptr)
		{
			SetCurrentLayer(layer);
		}
	}

	void Scene::CreateLayer(Camera* camera)
	{
		String name = std::to_string(m_LayerOrder.size()) + "_LAYER_NAMELESS_";
		CreateLayer(name, camera);
	}

	void Scene::SetCurrentLayer(const String& name)
	{
		m_CurrentLayer = m_Layers[name];
	}

	void Scene::SetCurrentLayer(int index)
	{
		m_CurrentLayer = m_LayerOrder[index];
	}

	void Scene::SetCurrentLayer(Layer* layer)
	{
		m_CurrentLayer = layer;
	}

	void Scene::AddEntity(Entity* entity)
	{
		if (HasLayer())
		{
			CurrentLayer().AddEntity(entity);
		}
	}

	void Scene::Update(double elapsedSeconds)
	{
	
	}

	String Scene::ToString() const
	{
		return "Scene";
	}

}