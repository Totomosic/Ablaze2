#include "Scene.h"
#include "SceneManager.h"

namespace Ablaze
{

	Scene::Scene() : Object()
	{
		m_CurrentLayer = nullptr;
		SceneManager::Instance().AddScene(this);
		SceneManager::Instance().LoadScene(this);
	}

	Scene::Scene(const String& layerName, GameObject* layerCamera) : Scene()
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

	std::vector<Layer*> Scene::GetLayers(int layerMask) const
	{
		std::vector<Layer*> layers;
		for (int i = 0; i < m_LayerOrder.size(); i++)
		{
			if (IsBitSet(layerMask, i))
			{
				layers.push_back(m_LayerOrder[i]);
			}
		}
		return layers;
	}

	Layer& Scene::CreateLayer(const String& name, GameObject* camera)
	{
		Layer* layer = nullptr;
		if (camera != nullptr)
		{
			layer = new Layer(name, camera);
		}
		else
		{
			layer = new Layer(name);
		}
		m_Layers[name] = layer;
		m_LayerOrder.push_back(layer);
		if (m_CurrentLayer == nullptr)
		{   
			SetCurrentLayer(layer);
		}
		return *layer;
	}

	Layer& Scene::CreateLayer(GameObject* camera)
	{
		String name = std::to_string(m_LayerOrder.size()) + "_LAYER_NAMELESS_";
		return CreateLayer(name, camera);
	}

	Layer& Scene::SetCurrentLayer(const String& name)
	{
		m_CurrentLayer = m_Layers[name];
		return *m_CurrentLayer;
	}

	Layer& Scene::SetCurrentLayer(int index)
	{
		m_CurrentLayer = m_LayerOrder[index];
		return *m_CurrentLayer;
	}

	Layer& Scene::SetCurrentLayer(Layer* layer)
	{
		m_CurrentLayer = layer;
		return *m_CurrentLayer;
	}

	void Scene::AddGameObject(GameObject* entity)
	{
		if (HasLayer())
		{
			CurrentLayer().AddGameObject(entity);
		}
	}

	const Layer& Scene::operator[](const String& layer) const
	{
		return GetLayer(layer);
	}

	Layer& Scene::operator[](const String& layer)
	{
		return GetLayer(layer);
	}

	String Scene::ToString() const
	{
		return "Scene";
	}

	void Scene::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.BeginArray("Layers");
		String filename = writer.Filename();
		size_t slash = filename.find_last_of('/');
		String dir = filename.substr(0, slash) + "/";
		for (Layer* layer : m_LayerOrder)
		{
			String fullpath = dir + "Layers/" + layer->GetName() + ".layer";
			layer->Serialize(JSONwriter(fullpath));
			writer.WriteElement(fullpath);
		}
		writer.EndArray();
		writer.EndObject();
	}

}