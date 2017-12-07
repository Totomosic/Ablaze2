#include "GameObject.h"
#include "SceneManager.h"
#include "ComponentSet.h"
#include "Components\__Components__.h"

#include "Resources\Meshes\Materials\__Materials__.h"

namespace Ablaze
{

	GameObject::GameObject() : Object(),
		m_Components(new ComponentSet(this)), m_Id(0), m_Layer(nullptr), m_Parent(nullptr), m_Tag("")
	{
		if (SceneManager::Instance().HasScene())
		{
			if (SceneManager::Instance().CurrentScene().HasLayer())
			{
				SceneManager::Instance().CurrentScene().CurrentLayer().AddGameObject(this);
			}
			else
			{
				AB_WARN("GameObject created with no active layer in current scene");
			}
		}
		else
		{
			AB_WARN("GameObject created with no active scene");
		}
	}

	GameObject::~GameObject()
	{
		delete m_Components;
		if (m_Layer != nullptr)
		{
			m_Layer->m_GameObjects[m_Id] = nullptr;
		}
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
		if (m_Layer != nullptr)
		{
			m_Layer->DestroyGameObject(this);
		}
		else
		{
			delete this;
		}
	}

	void GameObject::SetTag(const String& tag)
	{
		if (m_Layer != nullptr)
		{
			m_Layer->TagGameObject(this, tag);
		}
		m_Tag = tag;
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

	void GameObject::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("Tag", m_Tag);
		writer.WriteObject("Components", *m_Components);
		writer.EndObject();
	}

	void GameObject::Serialize(JSONwriter& writer, const String& parentFile) const
	{
		writer.BeginObject();
		writer.WriteAttribute("Tag", m_Tag);
		writer.WriteAttribute("Parent", parentFile);
		writer.WriteObject("Components", *m_Components);
		writer.EndObject();
	}

	GameObject* GameObject::Empty(const String& name)
	{
		GameObject* obj = new GameObject;
		obj->SetTag(name);
		return obj;
	}

	GameObject* GameObject::Instantiate(const String& name)
	{
		return Instantiate(name, 0, 0, 0);
	}

	GameObject* GameObject::Instantiate(const String& name, float x, float y, float z)
	{
		GameObject* object = new GameObject;
		object->AddComponent(new Transform(Maths::Vector3f(x, y, z)));
		object->SetTag(name);
		return object;
	}

	GameObject* GameObject::Instantiate(const String& name, GameObject* prefab)
	{
		GameObject* object = Instantiate(name);
		if (prefab != nullptr)
		{
			for (auto pair : prefab->Components().GetComponentMap())
			{
				object->Components().AddComponent(pair.first, pair.second->Clone());
			}
		}
		return object;
	}
	
	GameObject* GameObject::Instantiate(const String& name, GameObject* prefab, float x, float y, float z)
	{
		GameObject* object = Instantiate(name, prefab);
		object->AddComponent(new Transform(Maths::Vector3f(x, y, z)));
		return object;
	}

	GameObject* GameObject::Instantiate(const String& name, GameObject* prefab, GameObject* parent, float x, float y, float z)
	{
		GameObject* object = Instantiate(name, prefab);
		object->SetParent(parent);
		object->AddComponent(new Transform(Maths::Vector3f(x, y, z)));
		return object;
	}

	std::vector<GameObject*> GameObject::GetAll()
	{
		std::vector<GameObject*> objects;
		if (SceneManager::Instance().HasScene())
		{
			for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers())
			{
				for (GameObject* object : layer->GameObjects())
				{
					objects.push_back(object);
				}
			}
		}
		return objects;
	}

	std::vector<GameObject*> GameObject::GetAllWith(const std::vector<std::type_index>& componentTypes, bool onlyIfEnabled)
	{
		std::vector<GameObject*> objects;
		if (SceneManager::Instance().HasScene())
		{
			for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers())
			{
				for (GameObject* object : layer->GameObjects())
				{
					bool passed = true;
					for (const std::type_index& type : componentTypes)
					{
						if (!object->Components().HasComponent(type) || (onlyIfEnabled && !object->Components().GetComponent(type)->Enabled()))
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
		}
		return objects;
	}

}