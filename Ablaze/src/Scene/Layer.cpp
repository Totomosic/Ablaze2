#include "Layer.h"
#include "SceneManager.h"
#include "Application\Time.h"
#include "Components\__Components__.h"

namespace Ablaze
{

	Layer::Layer(const String& name, GameObject* camera) : Object(),
		 m_GameObjects(), m_Name(name)
	{
		Init();
		AddGameObject(camera);
		SetActiveCamera(camera);
	}

	Layer::Layer(const String& name) : Object(),
		m_GameObjects(), m_Name(name), m_Camera(nullptr)
	{
		Init();
	}

	Layer::~Layer()
	{
		for (GameObject* object : m_GameObjects)
		{
			delete object;
		}
	}

	const String& Layer::GetName() const
	{
		return m_Name;
	}

	const GameObject& Layer::GetActiveCamera() const
	{
		AB_ASSERT(m_Camera != nullptr, "Layer had no active Camera");
		return *m_Camera;
	}

	GameObject& Layer::GetActiveCamera()
	{
		AB_ASSERT(m_Camera != nullptr, "Layer had no active Camera");
		return *m_Camera;
	}

	bool Layer::HasCamera() const
	{
		return m_Camera != nullptr;
	}

	const std::vector<GameObject*>& Layer::GameObjects() const
	{
		return m_GameObjects;
	}

	void Layer::SetActiveCamera(GameObject* camera)
	{
		m_Camera = camera;
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		gameObject->m_Layer = this;
		m_GameObjects.push_back(gameObject);
	}

	void Layer::AddGameObject(GameObject* gameObject, const String& tag)
	{
		AddGameObject(gameObject);
		gameObject->SetTag(tag);
	}

	GameObject* Layer::CreateGameObject(const String& name)
	{
		GameObject* object = new GameObject;
		object->AddComponent<Transform>();
		object->AddComponent<MeshRenderer>();
		object->SetTag(name);
		return object;
	}

	GameObject* Layer::CreateGameObject(const String& name, float x, float y, float z)
	{
		GameObject* object = CreateGameObject(name);
		object->transform().SetLocalPosition(Maths::Vector3f(x, y, z));
		return object;
	}

	bool Layer::HasNamedGameObject(const String& tag) const
	{
		return m_NamedGameObjects.find(tag) != m_NamedGameObjects.end();
	}

	const GameObject& Layer::GetNamedGameObject(const String& tag, int index) const
	{
		return *m_NamedGameObjects.at(tag)[index];
	}

	GameObject& Layer::GetNamedGameObject(const String& tag, int index)
	{
		if (!TagExists(tag))
		{
			AB_ASSERT(false, "GameObject with tag: " + tag + " does not exist");
		}
		return *m_NamedGameObjects.at(tag)[index];
	}

	const GameObject& Layer::operator[](const String& tag) const
	{
		return GetNamedGameObject(tag);
	}

	GameObject& Layer::operator[](const String& tag)
	{
		return GetNamedGameObject(tag);
	}

	std::vector<GameObject*> Layer::GetNamedGameObjects(const String& tag) const
	{
		if (TagExists(tag))
		{
			return m_NamedGameObjects.at(tag);
		}
		return std::vector<GameObject*>();
	}

	void Layer::Clean()
	{
		std::vector<GameObjectContainer> continues;
		for (GameObjectContainer& container : m_NeedDelete)
		{
			GameObject* object = container.Obj;
			if (container.DeleteTime <= 0.0f)
			{
				if (m_NamedGameObjects.find(object->m_Tag) != m_NamedGameObjects.end())
				{
					auto it = std::find(m_NamedGameObjects[object->m_Tag].begin(), m_NamedGameObjects[object->m_Tag].end(), object);
					m_NamedGameObjects[object->m_Tag].erase(it);
				}
				auto it = std::find(m_GameObjects.begin(), m_GameObjects.end(), object);
				m_GameObjects.erase(it);
				delete object;
			}
			else
			{
				container.DeleteTime -= (float)Time::DeltaTime();
				continues.push_back(container);
			}
		}
		m_NeedDelete.clear();
		for (GameObjectContainer& c : continues)
		{
			m_NeedDelete.push_back(c);
		}
	}

	String Layer::ToString() const
	{
		return "Layer";
	}

	void Layer::Serialize(JSONwriter& writer) const
	{
		
	}

	void Layer::TagGameObject(GameObject* entity, const String& tag)
	{
		auto it = std::find(m_NamedGameObjects[entity->Tag()].begin(), m_NamedGameObjects[entity->Tag()].end(), entity);
		if (it != m_NamedGameObjects[entity->Tag()].end())
		{
			m_NamedGameObjects[entity->Tag()].erase(it);
		}

		if (TagExists(tag))
		{
			m_NamedGameObjects[tag].push_back(entity);
		}
		else
		{
			m_NamedGameObjects[tag] = std::vector<GameObject*>();
			m_NamedGameObjects[tag].push_back(entity);
		}
	}

	bool Layer::TagExists(const String& tag) const
	{
		return m_NamedGameObjects.find(tag) != m_NamedGameObjects.end();
	}

	void Layer::Init()
	{
		
	}

	String Layer::SerializeGameObject(JSONwriter& writer, GameObject* object, std::unordered_map<GameObject*, String>& mapping, const String& basePath, int& count) const
	{
		if (mapping.find(object) != mapping.end())
		{
			return mapping[object];
		}
		if (object->HasParent())
		{
			String parent = basePath + "GameObject" + std::to_string(count) + ".gameobject";
			parent = SerializeGameObject(*new JSONwriter(parent), object->Parent(), mapping, basePath, count);
			object->Serialize(writer, parent);
			mapping[object] = writer.Filename();
			count++;
			return writer.Filename();
		}
		else
		{
			object->Serialize(writer);
			mapping[object] = writer.Filename();
			count++;
			return writer.Filename();
		}
		
	}

	void Layer::DestroyGameObject(GameObject* object, float delay)
	{
		for (GameObjectContainer& c : m_NeedDelete)
		{
			if (c.Obj == object)
			{
				return;
			}
		}
		m_NeedDelete.push_back({ object, delay });
	}

}