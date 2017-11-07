#pragma once
#include "Common.h"
#include "Layer.h"

namespace Ablaze
{

	// Object that stores and manages all relavent Entities and Cameras
	class AB_API Scene : public Object
	{
	private:
		std::unordered_map<String, Layer*> m_Layers;
		std::vector<Layer*> m_LayerOrder;
		Layer* m_CurrentLayer;

	private:
		Scene();
		Scene(const String& layerName, GameObject* layerCamera = nullptr);
		~Scene();

	public:
		bool HasLayer() const;
		const Layer& CurrentLayer() const;
		Layer& CurrentLayer();
		const Layer& GetLayer(const String& layer) const;
		const Layer& GetLayer(int index) const;
		Layer& GetLayer(const String& layer);
		Layer& GetLayer(int index);
		const std::vector<Layer*>& GetLayers() const;

		Layer& CreateLayer(const String& name, GameObject* camera = nullptr);
		Layer& CreateLayer(GameObject* camera = nullptr); // Assigned random name
		Layer& SetCurrentLayer(const String& name);
		Layer& SetCurrentLayer(Layer* layer);
		Layer& SetCurrentLayer(int index);

		void AddGameObject(GameObject* entity);

		String ToString() const override;

		friend class SceneManager;

	};

}