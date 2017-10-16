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
		Scene(const String& layerName, Camera* layerCamera = nullptr);
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

		void CreateLayer(const String& name, Camera* camera = nullptr);
		void CreateLayer(Camera* camera = nullptr); // Assigned random name
		void SetCurrentLayer(const String& name);
		void SetCurrentLayer(Layer* layer);
		void SetCurrentLayer(int index);

		void AddEntity(Entity* entity);

		void Update(double elapsedSeconds);

		String ToString() const override;

		friend class SceneManager;

	};

}