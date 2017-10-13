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

		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);
		void RemoveScene(int index);

		String ToString() const override;

	};

}