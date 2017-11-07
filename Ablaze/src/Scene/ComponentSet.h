#pragma once
#include "Components\__Components__.h"
#include "Common.h"

namespace Ablaze
{

	class GameObject;

	class AB_API ComponentSet : public Object
	{
	private:
		GameObject* m_GameObject;
		std::unordered_map<std::type_index, Component*> m_Components;

	public:
		ComponentSet(GameObject* owner);

		int ComponentCount() const;
		GameObject* Owner() const;
		const std::vector<Component*> GetAll() const;

		Component* GetComponent(const std::type_index& type) const;
		bool HasComponent(const std::type_index& type) const;

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
			AddComponent(typeid(T), component);
		}

		String ToString() const override;

	private:
		void AddComponent(const std::type_index& type, Component* component);
		bool HasComponentType(const std::type_index& type) const;

	};

}