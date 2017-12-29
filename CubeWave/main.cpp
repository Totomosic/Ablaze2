#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::Maths;
using namespace Ablaze::VM;

#include "src\Wave.h"

namespace CubeWave
{

	class Sketch : public Application
	{
	public:
		Scene* scene;

	public:
		void Init() override
		{
			Window* window = new Window(1280, 720, "Sketch", Color::CornflowerBlue());
			Graphics::Initialise(window);

			scene = &SceneManager::Instance().CreateScene();
			Layer& worldLayer = scene->CreateLayer("World");
			scene->SetCurrentLayer("World");

			GameObject* camera = AddToScene(GameObject::Instantiate("Camera", 0, 0, 25))
				->AddComponent(new Camera());
			worldLayer.SetActiveCamera(camera);
			GameObject* light = AddToScene(GameObject::Instantiate("Light", 0, 50, 20))
				->AddComponent<Light>();

			int width = 13;
			GameObject* center = AddToScene(GameObject::Instantiate("Center", 0, 0, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Cube(), new Material(Color(0, 119, 190), ResourceManager::LightingColorShader()))));
			center->AddComponent(new Wave(center, -5.0f, 10.0f, 1.0f, 6.0f, sqrt(2 * (width / 2) * (width / 2))));

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (i == width / 2 && j == width / 2) continue;

					GameObject* cube = AddToScene(GameObject::Instantiate("Cube", center, j - width / 2, 0, i - width / 2));
					cube->MakeChildOf(center);
				}
			}

			center->transform().Rotate(PI / 4.0, Vector3f::Up());
			center->transform().Rotate(atan(1 / sqrt(2)), Vector3f::Right());

			GraphicsPipeline g;
			g.Renderer = new ForwardRenderer;
			g.Schedule = new RenderSchedule;
			g.Schedule->AddRenderPass(new RenderPass("Default"));
			Graphics::AddGraphicsPipeline(g);
		}

		void Tick() override
		{
			AB_INFO(Time::AvgFPS());
		}

		void Update() override
		{
			Transform& center = scene->GetLayer("World").GetNamedGameObject("Center").transform();
			center.Rotate(PI / 4.0 * Time::DeltaTime(), Vector3f::Up(), Space::Local);

			Application::Update();
		}

		void Render() override
		{
			Graphics::Clear();
			Graphics::RenderScene();
			Graphics::Present();
		}

	};

}

int main()
{
	CubeWave::Sketch sketch;
	sketch.Start();
	return 0;
}