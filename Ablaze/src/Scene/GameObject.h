#pragma once
#include "Common.h"
#include "Resources\Meshes\Materials\Material.h"

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
		String m_Tag;
		bool m_IsStatic;

	protected:
		GameObject();
		~GameObject();

	public:
		GameObject* Parent() const;
		bool HasParent() const;
		Layer* GetLayer() const;
		const String& Tag() const;
		bool IsStatic() const;

		void Enable() const;
		void Disable() const;
		void SetStatic(bool staticMode);
		void MakeStatic();
		void MakeDynamic();

		void SetParent(GameObject* parent);
		void MakeChildOf(GameObject* parent);
		void MakeStandalone();
		void Destroy(float delay = 0.0f);

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
		void Serialize(JSONwriter& writer) const;
		void Serialize(JSONwriter& writer, const String& parentFile) const;

		friend class Layer;
		friend class Engine;

	public:
		static GameObject* Empty(const String& name);
		static GameObject* Instantiate(const String& name);
		static GameObject* Instantiate(const String& name, float x, float y, float z);
		static GameObject* Instantiate(const String& name, GameObject* prefab);
		static GameObject* Instantiate(const String& name, GameObject* prefab, float x, float y, float z);
		static GameObject* Instantiate(const String& name, GameObject* prefab, GameObject* parent, float x, float y, float z);

		static std::vector<GameObject*> GetAll();
		static std::vector<GameObject*> GetAllWith(const std::vector<std::type_index>& componentTypes, bool onlyIfEnabled = true);

		template<typename T0>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0) }, onlyIfEnabled);
		}

		template<typename T0, typename T1>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0), typeid(T1) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2, typename T3>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3), typeid(T4) }, onlyIfEnabled);
		}

	};

}