#pragma once
#include "Common.h"

namespace Ablaze
{

	class Layer;
	class ComponentSet;
	class Transform;
	class Mesh;

	// Base class for all Objects in the game
	class AB_API GameObject : public Object
	{
	protected:
		ComponentSet* m_Components;
		uint m_Id;
		Layer* m_Layer;

		GameObject* m_Parent;

	protected:
		~GameObject();

	public:
		GameObject();

		GameObject* Parent() const;
		bool HasParent() const;
		Layer* GetLayer() const;

		void SetParent(GameObject* parent);
		void MakeChildOf(GameObject* parent);
		void MakeStandalone();
		void Destroy();

		void SetTag(const String& tag);

		const ComponentSet& Components() const;
		ComponentSet& Components();

		Transform& transform() const;
		Mesh& mesh() const;

		template<typename T>
		T& GetComponent() const
		{
			return *m_Components->GetComponent<T>();
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_Components->HasComponent<T>();
		}

		template<typename T>
		void AddComponent(T* component)
		{
			m_Components->AddComponent(component);
		}
		
		template<typename T>
		void AddComponent()
		{
			AddComponent(new T);
		}

		String ToString() const override;

		friend class Layer;
		friend class Engine;

	public:
		static GameObject* Empty();
		static GameObject* Instantiate();
		static GameObject* Instantiate(float x, float y, float z);
		static GameObject* Instantiate(GameObject* prefab);
		static GameObject* Instantiate(GameObject* prefab, float x, float y, float z);
		static GameObject* Instantiate(GameObject* prefab, GameObject* parent);
		static GameObject* Instantiate(GameObject* prefab, GameObject* parent, float x, float y, float z);

		static void Destroy(GameObject* gameObject);

		static std::vector<GameObject*> GetAll();
		static std::vector<GameObject*> GetAllWith(const std::vector<std::type_index>& componentTypes);

		template<typename T0>
		static std::vector<GameObject*> GetAllWith()
		{
			return GetAllWith({ typeid(T0) });
		}

		template<typename T0, typename T1>
		static std::vector<GameObject*> GetAllWith()
		{
			return GetAllWith({ typeid(T0), typeid(T1) });
		}

		template<typename T0, typename T1, typename T2>
		static std::vector<GameObject*> GetAllWith()
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2) });
		}

		template<typename T0, typename T1, typename T2, typename T3>
		static std::vector<GameObject*> GetAllWith()
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3) });
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4>
		static std::vector<GameObject*> GetAllWith()
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3), typeid(T4) });
		}

	};

}