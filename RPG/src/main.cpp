#include "Ablaze.h"

#include "Components\CameraController.h"
#include "Components\PlayerController.h"
#include "Components\NPCController.h"
#include "Components\Follow.h"

using namespace Ablaze;
using namespace Ablaze::Maths;
using namespace Ablaze::VM;

namespace Game
{

	class App : public Application
	{
	public:
		void Init() override
		{
			Window* window = new Window(1280, 720, "");
			Graphics::Initialise(window);

			SetFont("Roboto", new Font("res/Roboto-Black.ttf", 24));

			Scene& scene = SceneManager::Instance().CreateScene();
			Layer& main = scene.CreateLayer("Main");

			main.SetActiveCamera(AddToScene(GameObject::Instantiate("MainCamera", 0, 0, 20))
				->AddComponent(new Camera())
				->AddComponent(new RigidBody(false)));

			AddToScene(GameObject::Instantiate("Light", 0, 10, 0))
				->AddComponent<Light>();

			AddToScene(GameObject::Instantiate("Player", 15, 0, 15))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Cube(), Material(Color::White(), ResourceManager::LightingColorShader()))))
				->AddComponent(new PlayerController(10, PI / 3.0f));
			AddToScene(GameObject::Instantiate("PlayerOrientation", 0, 0, 0))
				->AddComponent(new CameraController(0.5f));
			main.GetNamedGameObject("PlayerOrientation").transform().Rotate(-PI / 2.5f, Vector3f::Right());

			AddToScene(GameObject::Instantiate("Boss", -15, 0, -15))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Cube(), Material(Color::Blue(), ResourceManager::LightingColorShader()))))
				->AddComponent(new NPCController(&main.GetNamedGameObject("Player"), 10, PI / 3.0f));

			AddToScene(GameObject::Instantiate("Bossroom", 0, -0.5f, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Plane(), Material(Color::Red(), ResourceManager::LightingColorShader())), Matrix4f::Scale(50, 1, 50)));

			main.GetNamedGameObject("PlayerOrientation").AddComponent(new Follow(&main.GetNamedGameObject("Player"), 100));
			main.GetActiveCamera().MakeChildOf(&main.GetNamedGameObject("PlayerOrientation"));

			Layer& ui = scene.CreateLayer("UI");
			scene.SetCurrentLayer("UI");

			ui.SetActiveCamera(AddToScene(GameObject::Instantiate("Canvas", 0, 0, 10))
				->AddComponent(new Camera(Projection::Orthographic)));

			scene.SetCurrentLayer("Main");
			
			GraphicsPipeline g;
			g.Renderer = new ForwardRenderer;
			g.Schedule = new RenderSchedule;
			g.Schedule->AddRenderPass(new RenderPass("Default"));
			Graphics::AddGraphicsPipeline(g);
		}

		void Tick() override
		{
			
		}

		void Update() override
		{
			Graphics::CurrentContext().SetTitle(std::to_string((int)Time::AvgFPS()));

			Camera& camera = SceneManager::Instance().CurrentScene()["Main"].GetActiveCamera().GetComponent<Camera>();
			Transform& player = SceneManager::Instance().CurrentScene()["Main"].GetNamedGameObject("Player").transform();

			Vector3f position = Input::MousePosition();
			position.z = camera.Owner()->transform().LocalPosition().z;
			Vector3f direction = camera.ScreenToWorldPoint(position) - player.Position();
			direction.y = 0.0f;
			direction = direction.Normalize();
			SceneManager::Instance().CurrentScene()["Main"].GetNamedGameObject("Player").transform().LocalRotation() = Quaternion::LookAt(direction);

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
	Game::App app;
	app.Start();
	return 0;
}