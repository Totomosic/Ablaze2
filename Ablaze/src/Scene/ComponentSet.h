#pragma once
#include "Common.h"

namespace Ablaze
{

	class GameObject;
	class Component;

	class AB_API ComponentSet : public Object
	{
	private:
		GameObject* m_GameObject;
		std::unordered_map<std::type_index, Component*> m_Components;

	public:
		ComponentSet(GameObject* owner);
		~ComponentSet();

		int ComponentCount() const;
		GameObject* Owner() const;
		std::vector<Component*> GetAll() const;
		const std::unordered_map<std::type_index, Component*>& GetComponentMap() const;

		Component* GetComponent(const std::type_index& type) const;
		bool HasComponent(const std::type_index& type) const;
		void RemoveComponent(Component* component, float delay = 0.0f);
		void RemoveComponent(const std::type_index& type, float delay = 0.0f);

		template<typename T>
		T* GetComponent() const
		{
			return (T*)GetComponent(typeid(T));
		}

		template<typename T>
		bool HasComponent() const
		{
			return HasComponent(typeid(T));
		}

		template<typename T>
		void AddComponent(T* component)
		{
			AddComponent(typeid(*component), component);
		}

		template<typename T>
		void RemoveComponent(float delay = 0.0f)
		{
			RemoveComponent(typeid(T), delay);
		}

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;

		friend class GameObject;

	private:
		void AddComponent(const std::type_index& type, Component* component);
		bool HasComponentType(const std::type_index& type) const;
		void DeleteComponent(Component* component);

	};

}