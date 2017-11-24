#pragma once
#include "Common.h"
#include "Scene.h"

namespace Ablaze
{

	class AB_API SceneManager : public Object
	{
	private:
		std::vector<Scene*> m_Scenes;
		Scene* m_Current;

	private:
		SceneManager();

	public:
		static SceneManager& Instance();

	public:
		Scene& CurrentScene();
		int SceneCount() const;
		bool HasScene() const;

		void LoadScene(int index);
		void LoadScene(Scene* scene);
		Scene& LoadScene(const String& sceneFile);
		void SaveScene(Scene& scene, const String& file);

		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);
		void RemoveScene(int index);

		Scene& CreateScene();

		String ToString() const override;

	};

}