#include "Layer.h"
#include "SceneManager.h"

namespace Ablaze
{

	Layer::Layer(const String& name, GameObject* camera) : Object(),
		m_MaxGameObjects(100000), m_HighestID(0), m_GameObjects(new GameObject*[m_MaxGameObjects]), m_Name(name)
	{
		Init();
		AddGameObject(camera);
		SetActiveCamera(camera);
	}

	Layer::Layer(const String& name) : Object(),
		m_MaxGameObjects(100000), m_HighestID(0), m_GameObjects(new GameObject*[m_MaxGameObjects]), m_Name(name), m_Camera(nullptr)
	{
		Init();
	}

	Layer::~Layer()
	{
		AB_INFO("LAYER DESTROYED");
	}

	const String& Layer::GetName() const
	{
		return m_Name;
	}

	GameObject* Layer::GetActiveCamera() const
	{
		return m_Camera;
	}

	bool Layer::HasCamera() const
	{
		return m_Camera != nullptr;
	}

	std::vector<GameObject*> Layer::GameObjects() const
	{
		std::vector<GameObject*> objects;
		for (uint i = 0; i < m_HighestID + 1; i++)
		{
			if (m_GameObjects[i] != nullptr)
			{
				objects.push_back(m_GameObjects[i]);
			}
		}
		return objects;
	}

	void Layer::SetActiveCamera(GameObject* camera)
	{
		m_Camera = camera;
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		uint id = GetNextID();
		gameObject->m_Id = id;
		m_GameObjects[id] = gameObject;
		gameObject->m_Layer = this;
	}

	void Layer::AddGameObject(GameObject* gameObject, const String& tag)
	{
		AddGameObject(gameObject);
		TagGameObject(gameObject, tag);
	}

	const GameObject& Layer::GetNamedGameObject(const String& tag, int index) const
	{
		return *m_NamedGameObjects.at(tag)[index];
	}

	GameObject& Layer::GetNamedGameObject(const String& tag, int index)
	{
		if (!TagExists(tag))
		{
			AB_ERROR("GameObject with tag: " + tag + " does not exist");
			return *(GameObject*)nullptr;
		}
		return *m_NamedGameObjects.at(tag)[index];
	}

	const std::vector<GameObject*> Layer::GetNamedGameObjects(const String& tag) const
	{
		if (TagExists(tag))
		{
			return m_NamedGameObjects.at(tag);
		}
		return std::vector<GameObject*>();
	}

	String Layer::ToString() const
	{
		return "Layer";
	}

	void Layer::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("Name", m_Name);
		writer.BeginArray("GameObjects");
		String filename = writer.Filename();
		size_t slash = filename.find_last_of('/');

		std::unordered_map<GameObject*, String> mapping;
		String baseFilepath = filename.substr(0, slash) + "/" + GetName() + "/";
		String cameraFile = "";

		int count = 0;
		for (int i = 0; i < m_HighestID + 1; i++)
		{			
			if (m_GameObjects[i] != nullptr)
			{
				String fullFilename = baseFilepath + "GameObject" + std::to_string(i) + ".gameobject";
				SerializeGameObject(JSONwriter(fullFilename), m_GameObjects[i], mapping, baseFilepath, count);
				writer.WriteElement(fullFilename);
				if (m_GameObjects[i] == m_Camera)
				{
					cameraFile = fullFilename;
				}
			}
		}
		writer.EndArray();
		writer.WriteAttribute("Camera", cameraFile);
		writer.EndObject();
	}

	void Layer::TagGameObject(GameObject* entity, const String& tag)
	{
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

	uint Layer::GetNextID()
	{
		for (uint i = 0; i < m_HighestID + 2; i++)
		{
			if (m_GameObjects[i] == nullptr)
			{
				if (i > m_HighestID)
				{
					m_HighestID = i;
				}
				return i;
			}
		}
		AB_ERROR("Unable to find available ID for GameObject");
		return 0;
	}

	void Layer::Init()
	{
		for (uint i = 0; i < m_MaxGameObjects; i++)
		{
			m_GameObjects[i] = nullptr;
		}
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

	void Layer::DestroyGameObject(GameObject* object)
	{
		if (m_NamedGameObjects.find(object->m_Tag) != m_NamedGameObjects.end())
		{
			auto it = std::find(m_NamedGameObjects[object->m_Tag].begin(), m_NamedGameObjects[object->m_Tag].end(), object);
			m_NamedGameObjects[object->m_Tag].erase(it);
		}
		delete object;
		object = nullptr;
	}

}