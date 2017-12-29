#pragma once
#include "Common.h"
#include "Scene.h"

namespace Ablaze
{

	class AB_API SceneManager : public Singleton<SceneManager>
	{
	private:
		std::vector<Scene*> m_Scenes;
		Scene* m_Current;

	private:
		SceneManager();

	public:
		Scene& CurrentScene();
		int SceneCount() const;
		bool HasScene() const;

		void LoadScene(int index);
		void LoadScene(Scene* scene);
		void SaveScene(Scene& scene, const String& file);

		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);
		void RemoveScene(int index);

		Scene& CreateScene();

		friend class Singleton<SceneManager>;

	};

	GameObject* AddToScene(GameObject* object);

}