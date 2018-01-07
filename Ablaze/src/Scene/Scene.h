#pragma once
#include "Common.h"
#include "Layer.h"

namespace Ablaze
{

	struct LayerMask;

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
		bool HasLayer(const String& layerName) const;
		const Layer& CurrentLayer() const;
		Layer& CurrentLayer();
		const Layer& GetLayer(const String& layer) const;
		Layer& GetLayer(const String& layer);
		const Layer& GetLayer(int index) const;
		Layer& GetLayer(int index);
		const std::vector<Layer*>& GetLayers() const;
		std::vector<Layer*> GetLayers(int layerMask) const;
		std::vector<Layer*> GetLayers(const LayerMask& layerMask) const;
		int GetMask(Layer* layer) const;
		int GetMask(const String& layerName) const;

		Layer& CreateLayer(const String& name, GameObject* camera = nullptr);
		Layer& CreateLayer(GameObject* camera = nullptr); // Assigned random name
		Layer& SetCurrentLayer(const String& name);
		Layer& SetCurrentLayer(Layer* layer);
		Layer& SetCurrentLayer(int index);

		void AddLayer(Layer* layer);

		const Layer& operator[](const String& layer) const;
		Layer& operator[](const String& layer);

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;

		friend class SceneManager;

	};

}