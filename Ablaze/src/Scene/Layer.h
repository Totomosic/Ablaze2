#pragma once
#include "Common.h"
#include "GameObject.h"

namespace Ablaze
{

	class AB_API Layer : public Object
	{
	private:
		struct AB_API GameObjectContainer
		{
			GameObject* Obj;
			float DeleteTime;
		};

	private:
		std::vector<GameObject*> m_GameObjects;

		String m_Name;
		std::unordered_map<String, std::vector<GameObject*>> m_NamedGameObjects;
		GameObject* m_Camera;

		std::vector<GameObjectContainer> m_NeedDelete;

	private:
		Layer(const String& name, GameObject* camera);
		Layer(const String& name);
		Layer(const Layer& other) = delete;
		~Layer();

	public:
		const String& GetName() const;
		bool HasCamera() const;
		const std::vector<GameObject*>& GameObjects() const;
		
		const GameObject& GetActiveCamera() const;
		GameObject& GetActiveCamera();
		void SetActiveCamera(GameObject* camera);

		const GameObject& GetNamedGameObject(const String& tag, int index = 0) const;
		GameObject& GetNamedGameObject(const String& tag, int index = 0);
		std::vector<GameObject*> GetNamedGameObjects(const String& tag) const;

		void AddGameObject(GameObject* gameObject);
		void AddGameObject(GameObject* gameObject, const String& tag);
		GameObject* CreateGameObject(const String& name);
		GameObject* CreateGameObject(const String& name, float x, float y, float z);

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

		void Clean();

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;

		friend class Scene;
		friend class GameObject;
		friend class Application;

	private:
		void TagGameObject(GameObject* entity, const String& tag);
		bool TagExists(const String& tag) const;

		void Init();
		void DestroyGameObject(GameObject* object, float delay = 0.0f);

		String SerializeGameObject(JSONwriter& writer, GameObject* object, std::unordered_map<GameObject*, String>& mapping, const String& basePath, int& count) const;

	};

}