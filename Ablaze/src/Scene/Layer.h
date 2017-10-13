#pragma once
#include "Common.h"
#include "Entity.h"
#include "Camera.h"

namespace Ablaze
{

	class AB_API Layer : public Object
	{
	private:
		const String& m_Name;
		std::vector<Entity*> m_Entities;
		Camera* m_Camera;

	private:
		Layer(const String& name, Camera* camera);
		Layer(const String& name);
		Layer(const Layer& other) = delete;
		~Layer();

	public:
		const String& GetName() const;
		const std::vector<Entity*>& GetEntities() const;
		Camera* GetCamera() const;
		bool HasCamera() const;

		void SetCamera(Camera* camera);
		void AddEntity(Entity* entity);
		void RemoveEntity(Entity* entity);
		void RemoveEntity(int index);
		void Clear();

		String ToString() const override;

		friend class Scene;

	};

}