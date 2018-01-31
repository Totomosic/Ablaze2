#include "GameObject.h"
#include "SceneManager.h"
#include "ComponentSet.h"
#include "Components\__Components__.h"
#include "LayerMask.h"
#include "Application\Time.h"

#include "Resources\Meshes\Materials\__Materials__.h"

namespace Ablaze
{

	GameObject::GameObject() : Object(),
		m_Components(new ComponentSet(this)), m_Layer(nullptr), m_Parent(nullptr), m_Tag("")
	{

	}

	GameObject::~GameObject()
	{
		delete m_Components;
		if (m_Parent != nullptr)
		{
			m_Parent->RemoveChild(this);
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

	bool GameObject::HasChild() const
	{
		return ChildCount() != 0;
	}

	const std::vector<GameObject*> GameObject::Children() const
	{
		return m_Children;
	}

	GameObject* GameObject::GetChild(int index) const
	{
		AB_ASSERT(index < ChildCount(), "Index Out of range");
		return m_Children[index];
	}

	int GameObject::ChildCount() const
	{
		return m_Children.size();
	}

	Layer* GameObject::GetLayer() const
	{
		return m_Layer;
	}

	const String& GameObject::Tag() const
	{
		return m_Tag;
	}

	bool GameObject::IsStatic() const
	{
		return m_IsStatic;
	}

	void GameObject::Enable() const
	{
		for (Component* c : m_Components->GetAll())
		{
			c->Enable();
		}
	}

	void GameObject::Disable() const
	{
		for (Component* c : m_Components->GetAll())
		{
			c->Disable();
		}
	}

	void GameObject::SetStatic(bool staticMode)
	{
		m_IsStatic = staticMode;
	}

	void GameObject::MakeStatic()
	{
		SetStatic(true);
	}

	void GameObject::MakeDynamic()
	{
		SetStatic(false);
	}

	void GameObject::SetParent(GameObject* parent)
	{
		if (parent == nullptr && m_Parent != nullptr)
		{
			m_Parent->RemoveChild(this);
		}
		m_Parent = parent;
		if (parent != nullptr)
		{
			parent->AddChild(this);
		}
	}

	void GameObject::MakeChildOf(GameObject* parent)
	{
		SetParent(parent);
	}

	void GameObject::MakeStandalone()
	{
		MakeChildOf(nullptr);
	}

	void GameObject::Destroy(float delay)
	{
		if (m_Layer == nullptr)
		{
			delete this;
			return;
		}
		m_Layer->DestroyGameObject(this, delay);
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

	MeshRenderer& GameObject::mesh() const
	{
		return GetComponent<MeshRenderer>();
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

	void GameObject::AddChild(GameObject* object)
	{
		m_Children.push_back(object);
	}

	void GameObject::RemoveChild(GameObject* object)
	{
		auto it = std::find(m_Children.begin(), m_Children.end(), object);
		AB_ASSERT(it != m_Children.end(), "Child did not exist");
		m_Children.erase(it);
	}

	void GameObject::Clean()
	{
		std::vector<ComponentContainer> continues;
		for (ComponentContainer& container : m_NeedDelete)
		{
			Component* object = container.Comp;
			if (container.DeleteTime <= 0.0f)
			{
				m_Components->DeleteComponent(object);
			}
			else
			{
				container.DeleteTime -= (float)Time::DeltaTime();
				continues.push_back(container);
			}
		}
		m_NeedDelete.clear();
		for (ComponentContainer& c : continues)
		{
			m_NeedDelete.push_back(c);
		}
	}

	void GameObject::DestroyComponent(Component* component, float deleteTime)
	{
		for (ComponentContainer& c : m_NeedDelete)
		{
			if (c.Comp == component)
			{
				return;
			}
		}
		m_NeedDelete.push_back({ component, deleteTime });
	}

	GameObject* GameObject::Empty(const String& name)
	{
		return SceneManager::Instance().CurrentScene().CurrentLayer().CreateGameObject(name);
	}

	GameObject* GameObject::Instantiate(const String& name)
	{
		return Instantiate(name, 0, 0, 0);
	}

	GameObject* GameObject::Instantiate(const String& name, float x, float y, float z)
	{
		return SceneManager::Instance().CurrentScene().CurrentLayer().CreateGameObject(name, x, y, z);
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

	std::vector<GameObject*> GameObject::GetAll(const LayerMask& mask)
	{
		std::vector<GameObject*> objects;
		if (SceneManager::Instance().HasScene())
		{
			for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers(mask))
			{
				for (GameObject* object : layer->GameObjects())
				{
					objects.push_back(object);
				}
			}
		}
		return objects;
	}

	std::vector<GameObject*> GameObject::GetAll()
	{
		return GetAll(LayerMask());
	}

	std::vector<GameObject*> GameObject::FindAllWith(const std::vector<std::type_index>& componentTypes, const LayerMask& mask, bool onlyIfEnabled)
	{
		std::vector<GameObject*> objects;
		if (SceneManager::Instance().HasScene())
		{
			for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers(mask))
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

	std::vector<GameObject*> GameObject::FindAllWith(const std::vector<std::type_index>& componentTypes, bool onlyIfEnabled)
	{
		return FindAllWith(componentTypes, LayerMask(), onlyIfEnabled);
	}

	std::vector<GameObject*> GameObject::FindAllWithTag(const String& tag, const LayerMask& mask)
	{
		std::vector<GameObject*> result;
		for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers(mask))
		{
			std::vector<GameObject*> objects = layer->GetNamedGameObjects(tag);
			result.insert(result.end(), objects.begin(), objects.end());
		}
		return result;
	}

	std::vector<GameObject*> GameObject::FindAllWithTag(const String& tag)
	{
		return FindAllWithTag(tag, LayerMask());
	}

	GameObject* GameObject::FindWithTag(const String& tag, const LayerMask& mask)
	{
		for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers(mask))
		{
			if (layer->HasNamedGameObject(tag))
			{
				return &layer->GetNamedGameObject(tag);
			}
		}
		return nullptr;
	}

	GameObject* GameObject::FindWithTag(const String& tag)
	{
		return FindWithTag(tag, LayerMask());
	}

}