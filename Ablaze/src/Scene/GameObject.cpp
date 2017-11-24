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
				SceneManager::Instance().CurrentScene().AddGameObject(this);
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

	GameObject* GameObject::Deserialize(JSONnode& node)
	{
		GameObject* obj = Empty(node["Tag"].Data());
		delete obj->m_Components;		 
		obj->m_Components = ComponentSet::Deserialize(node["Components"], obj);
		return obj;
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
		object->AddComponent(new Transform(Maths::Vec3(x, y, z)));
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
		object->AddComponent(new Transform(Maths::Vec3(x, y, z)));
		return object;
	}

	GameObject* GameObject::Instantiate(const String& name, GameObject* prefab, GameObject* parent)
	{
		GameObject* object = Instantiate(name, prefab);
		object->SetParent(parent);
		return object;
	}

	GameObject* GameObject::Instantiate(const String& name, GameObject* prefab, GameObject* parent, float x, float y, float z)
	{
		GameObject* object = Instantiate(name, prefab, parent);
		object->AddComponent(new Transform(Maths::Vec3(x, y, z)));
		return object;
	}

	GameObject* GameObject::Load(const String& gameobjectFile)
	{
		JSONnode& node = *LoadJSONFile(gameobjectFile);
		GameObject* object = Empty(node["Tag"].Data());

		if (node.HasChild("Components"))
		{
			JSONnode& components = node["Components"];
			if (components.HasChild("Transform"))
			{
				LoadTransform(object, components["Transform"]);
			}
			if (components.HasChild("Mesh"))
			{
				LoadMesh(object, components["Mesh"]);
			}
		}
		if (node.HasChild("Parent"))
		{
			object->SetParent(Load(node["Parent"].Data()));
		}
		return object;
	}

	void GameObject::Destroy(GameObject* gameObject)
	{
		delete gameObject;
		gameObject = nullptr;
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

	void GameObject::LoadTransform(GameObject* object, JSONnode& transformNode)
	{
		Transform* transform = new Transform;
		if (transformNode.HasChild("Position"))
		{
			JSONnode& position = transformNode["Position"];
			transform->LocalPosition().x = stof(position["x"].Data());
			transform->LocalPosition().y = stof(position["y"].Data());
			transform->LocalPosition().z = stof(position["z"].Data());
		}
		if (transformNode.HasChild("Rotation"))
		{
			JSONnode& rotation = transformNode["Rotation"];
			transform->LocalRotation().x = stof(rotation["x"].Data());
			transform->LocalRotation().y = stof(rotation["y"].Data());
			transform->LocalRotation().z = stof(rotation["z"].Data());
			transform->LocalRotation().w = stof(rotation["w"].Data());
		}
		if (transformNode.HasChild("Scale"))
		{
			JSONnode& scale = transformNode["Scale"];
			transform->LocalScale().x = stof(scale["x"].Data());
			transform->LocalScale().y = stof(scale["y"].Data());
			transform->LocalScale().z = stof(scale["z"].Data());
		}
		object->AddComponent(transform);
	}

	void GameObject::LoadMesh(GameObject* object, JSONnode& meshNode)
	{
		Mesh* mesh = new Mesh;
		if (meshNode.HasChild("Model"))
		{
			if (meshNode.HasChild("Material"))
			{
				JSONnode& materialNode = meshNode["Material"];
				if (!materialNode.HasChild("Type") || materialNode["Type"].Data() == "Texture2D")
				{
					LoadMaterial<Texture2D>(mesh, meshNode);
				}
			}
			else
			{
				AB_WARN("No Material tag found with model tag");
			}
		}

		object->AddComponent(mesh);
	}

}