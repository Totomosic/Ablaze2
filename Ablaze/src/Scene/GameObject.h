#pragma once
#include "Common.h"
#include "Resources\Meshes\Materials\Material.h"

namespace Ablaze
{

	class Component;
	class Layer;
	struct LayerMask;
	class ComponentSet;
	class Transform;
	class MeshRenderer;

	// Base class for all Objects in the game
	class AB_API GameObject : public Object
	{
	private:
		struct AB_API ComponentContainer
		{
			Component* Comp;
			float DeleteTime;
		};

	protected:
		ComponentSet* m_Components;

		Layer* m_Layer;
		GameObject* m_Parent;
		std::vector<GameObject*> m_Children;
		String m_Tag;
		bool m_IsStatic;

		std::vector<ComponentContainer> m_NeedDelete;

	protected:
		GameObject();
		~GameObject();

	public:
		GameObject* Parent() const;
		bool HasParent() const;
		bool HasChild() const;
		const std::vector<GameObject*> Children() const;
		GameObject* GetChild(int index) const;
		int ChildCount() const;
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
		MeshRenderer& mesh() const;

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
		GameObject* AddComponent(T* component)
		{
			m_Components->AddComponent(component);
			return this;
		}
		
		template<typename T>
		GameObject* AddComponent()
		{
			return AddComponent(new T);
		}

		template<typename T>
		void RemoveComponent()
		{
			return m_Components->RemoveComponent<T>();
		}

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;
		void Serialize(JSONwriter& writer, const String& parentFile) const;

		friend class Layer;
		friend class Engine;
		friend class ComponentSet;

	private:
		void AddChild(GameObject* object);
		void RemoveChild(GameObject* object);

		void Clean();
		void DestroyComponent(Component* component, float deleteTime = 0.0f);

	public:
		static GameObject* Empty(const String& name);
		static GameObject* Instantiate(const String& name);
		static GameObject* Instantiate(const String& name, float x, float y, float z);
		static GameObject* Instantiate(const String& name, GameObject* prefab);
		static GameObject* Instantiate(const String& name, GameObject* prefab, float x, float y, float z);

		static std::vector<GameObject*> GetAll(const LayerMask& mask);
		static std::vector<GameObject*> GetAll();
		static std::vector<GameObject*> FindAllWith(const std::vector<std::type_index>& componentTypes, const LayerMask& mask, bool onlyIfEnabled = true);
		static std::vector<GameObject*> FindAllWith(const std::vector<std::type_index>& componentTypes, bool onlyIfEnabled = true);
		static std::vector<GameObject*> FindAllWithTag(const String& tag, const LayerMask& mask);
		static std::vector<GameObject*> FindAllWithTag(const String& tag);
		static GameObject* FindWithTag(const String& tag, const LayerMask& mask);
		static GameObject* FindWithTag(const String& tag);

		template<typename T0>
		static std::vector<GameObject*> FindAllWith(const LayerMask& mask, bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0) }, mask, onlyIfEnabled);
		}

		template<typename T0, typename T1>
		static std::vector<GameObject*> FindAllWith(const LayerMask& mask, bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0), typeid(T1) }, mask, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2>
		static std::vector<GameObject*> FindAllWith(const LayerMask& mask, bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0), typeid(T1), typeid(T2) }, mask, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2, typename T3>
		static std::vector<GameObject*> FindAllWith(const LayerMask& mask, bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3) }, mask, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4>
		static std::vector<GameObject*> FindAllWith(const LayerMask& mask, bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3), typeid(T4) }, mask, onlyIfEnabled);
		}

		template<typename T0>
		static std::vector<GameObject*> FindAllWith(bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0) }, onlyIfEnabled);
		}

		template<typename T0, typename T1>
		static std::vector<GameObject*> FindAllWith(bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0), typeid(T1) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2>
		static std::vector<GameObject*> FindAllWith(bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0), typeid(T1), typeid(T2) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2, typename T3>
		static std::vector<GameObject*> FindAllWith(bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4>
		static std::vector<GameObject*> FindAllWith(bool onlyIfEnabled = true)
		{
			return FindAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3), typeid(T4) }, onlyIfEnabled);
		}

	};

}