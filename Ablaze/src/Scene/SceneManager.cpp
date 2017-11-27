#include "SceneManager.h"

namespace Ablaze
{

	SceneManager::SceneManager() : Object()
	{
		m_Current = nullptr;
	}

	SceneManager& SceneManager::Instance()
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	Scene& SceneManager::CurrentScene()
	{
		return *m_Current;
	}

	int SceneManager::SceneCount() const
	{
		return m_Scenes.size();
	}

	bool SceneManager::HasScene() const
	{
		return m_Current != nullptr;
	}

	void SceneManager::LoadScene(int index)
	{
		m_Current = m_Scenes[index];
	}

	void SceneManager::LoadScene(Scene* scene)
	{
		m_Current = scene;
	}

	void SceneManager::SaveScene(Scene& scene, const String& file)
	{
		scene.Serialize(JSONwriter(file));
	}

	void SceneManager::AddScene(Scene* scene)
	{
		m_Scenes.push_back(scene);
		if (!HasScene())
		{
			LoadScene(scene);
		}
	}

	void SceneManager::RemoveScene(int index)
	{
		m_Scenes.erase(m_Scenes.begin() + index);
	}

	void SceneManager::RemoveScene(Scene* scene)
	{
		auto it = std::find(m_Scenes.begin(), m_Scenes.end(), scene);
		m_Scenes.erase(it);
	}

	Scene& SceneManager::CreateScene()
	{
		Scene* s = new Scene();
		return *s;
	}

	String SceneManager::ToString() const
	{
		return "SceneManager";
	}

}