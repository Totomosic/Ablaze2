#pragma once
#include "Common.h"
#include "Entity.h"
#include "Camera.h"

namespace Ablaze
{

	// Object that stores and manages all relavent Entities and Cameras
	class AB_API Scene : public Object
	{
	private:
		std::vector<Entity*> m_Entities;
		std::vector<Camera*> m_Cameras;

	public:
		Scene();
		~Scene();

		const std::vector<Entity*>& GetEntities() const;
		const std::vector<Camera*>& GetCameras() const;
		int EntityCount() const;
		int CameraCount() const;

		// Adding an entity transfers complete ownership to scene object
		void AddEntity(Entity* entity);
		void AddCamera(Camera* camera);
		void RemoveEntity(Entity* entity);
		void RemoveEntity(int index);
		void RemoveCamera(Camera* camera);
		void RemoveCamera(int index);
		void ClearEntities();
		void ClearCameras();

		const Entity& GetEntity(int index) const;
		Entity& GetEntity(int index);
		const Camera& GetCamera(int index) const;
		Camera& GetCamera(int index);

		String ToString() const override;

	};

}