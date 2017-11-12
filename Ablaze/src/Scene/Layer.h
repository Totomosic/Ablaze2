#pragma once
#include "Common.h"
#include "GameObject.h"

namespace Ablaze
{

	class AB_API Layer : public Object
	{
	private:
		uint m_MaxGameObjects;
		uint m_HighestID;
		GameObject** m_GameObjects;

		const String& m_Name;
		std::unordered_map<String, std::vector<GameObject*>> m_NamedEntities;
		GameObject* m_Camera;

	private:
		Layer(const String& name, GameObject* camera);
		Layer(const String& name);
		Layer(const Layer& other) = delete;
		~Layer();

	public:
		const String& GetName() const;
		bool HasCamera() const;
		std::vector<GameObject*> GameObjects() const;
		
		GameObject* GetActiveCamera() const;
		void SetActiveCamera(GameObject* camera);

		const GameObject& GetNamedGameObject(const String& tag, int index = 0) const;
		GameObject& GetNamedGameObject(const String& tag, int index = 0);

		void AddGameObject(GameObject* gameObject);
		void AddGameObject(GameObject* gameObject, const String& tag);

		template<typename T>
		const T& GetNamedGameObject(const String& tag, int index = 0) const
		{
			return *((T*)&GetNamedGameObject(tag, index));
		}

		template<typename T>
		T& GetNamedGameObject(const String& tag, int index = 0)
		{
			return *((T*)&GetNamedGameObject(tag, index));
		}

		String ToString() const override;

		friend class Scene;
		friend class GameObject;

	private:
		void TagGameObject(GameObject* entity, const String& tag);
		bool TagExists(const String& tag);

		uint GetNextID();
		void Init();

	};

}