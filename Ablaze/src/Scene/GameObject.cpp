#include "GameObject.h"
#include "SceneManager.h"
#include "ComponentSet.h"
#include "Components\__Components__.h"

namespace Ablaze
{

	GameObject::GameObject() : Object(),
		m_Components(new ComponentSet(this)), m_Id(0), m_Layer(nullptr), m_Parent(nullptr)
	{
		if (SceneManager::Instance().HasScene())
		{
			if (SceneManager::Instance().CurrentScene().HasLayer())
			{
				SceneManager::Instance().CurrentScene().AddGameObject(this);
			}
		}
	}

	GameObject::~GameObject()
	{
		delete m_Components;
		m_Layer->m_GameObjects[m_Id] = nullptr;
	}

	GameObject* GameObject::Parent() const
	{
		return m_Parent;
	}

	bool GameObject::HasParent() const
	{
		return m_Parent != nullptr;
	}

	Layer* GameObject::GetLayer() const
	{
		return m_Layer;
	}

	void GameObject::SetParent(GameObject* parent)
	{
		m_Parent = parent;
	}

	void GameObject::MakeChildOf(GameObject* parent)
	{
		SetParent(parent);
	}

	void GameObject::MakeStandalone()
	{
		MakeChildOf(nullptr);
	}

	void GameObject::Destroy()
	{
		Destroy(this);
	}

	void GameObject::SetTag(const String& tag)
	{
		m_Layer->TagGameObject(this, tag);
	}
	
	const ComponentSet& GameObject::Components() const
	{
		return *m_Components;
	}

	ComponentSet& GameObject::Components()
	{
		return *m_Components;
	}

	Transform& GameObject::transform() const
	{
		return GetComponent<Transform>();
	}

	Mesh& GameObject::mesh() const
	{
		return GetComponent<Mesh>();
	}

	String GameObject::ToString() const
	{
		return "GameObject";
	}

	GameObject* GameObject::Instantiate()
	{
		return new GameObject();
	}

	GameObject* GameObject::Instantiate(float x, float y, float z)
	{
		GameObject* object = new GameObject;
		object->AddComponent(new Transform(Maths::Vec3(x, y, z)));
		return object;
	}

	GameObject* GameObject::Instantiate(GameObject* prefab)
	{
		GameObject* object = new GameObject;
		for (auto pair : prefab->Components().GetComponentMap())
		{
			object->Components().AddComponent(pair.first, pair.second->Clone());
		}
		return object;
	}
	
	GameObject* GameObject::Instantiate(GameObject* prefab, float x, float y, float z)
	{
		GameObject* object = Instantiate(prefab);
		object->AddComponent(new Transform(Maths::Vec3(x, y, z)));
		return object;
	}

	GameObject* GameObject::Instantiate(GameObject* prefab, GameObject* parent)
	{
		GameObject* object = Instantiate(prefab);
		object->SetParent(parent);
		return object;
	}

	GameObject* GameObject::Instantiate(GameObject* prefab, GameObject* parent, float x, float y, float z)
	{
		GameObject* object = Instantiate(prefab, parent);
		object->AddComponent(new Transform(Maths::Vec3(x, y, z)));
		return object;
	}

	void GameObject::Destroy(GameObject* gameObject)
	{
		delete gameObject;
		gameObject = nullptr;
	}

	std::vector<GameObject*> GameObject::GetAllWith(const std::vector<std::type_index>& componentTypes)
	{
		std::vector<GameObject*> objects;
		for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers())
		{
			for (GameObject* object : layer->GameObjects())
			{
				bool passed = true;
				for (const std::type_index& type : componentTypes)
				{
					if (!object->Components().HasComponent(type))
					{
						passed = false;
						break;
					}
				}
				if (passed)
				{
					objects.push_back(object);
				}
			}
		}
		return objects;
	}

	std::vector<GameObject*> GameObject::GetAllWith(const std::type_index& componentType)
	{
		return GetAllWith({ componentType });
	}

}