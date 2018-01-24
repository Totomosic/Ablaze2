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

			RenderTexture* cam0 = new RenderTexture(512, 512, LayerMask("Main"));
			RenderTexture* cam1 = new RenderTexture(512, 512, LayerMask("Main"));
			RenderTexture* cam2 = new RenderTexture(512, 512, LayerMask("Main"));
			RenderTexture* cam3 = new RenderTexture(512, 512, LayerMask("Main"));

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

			main["PlayerOrientation"].transform().Rotate(-PI / 2.5f, Vector3f::Right());

			AddToScene(GameObject::Instantiate("Boss", -15, 0, -15))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Cube(), Material(Color::Blue(), ResourceManager::LightingColorShader()))))
				->AddComponent(new NPCController(&main["Player"], 10, PI / 3.0f));

			AddToScene(GameObject::Instantiate("Bossroom", 0, -0.5f, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Plane(), Material(Color::Red(), ResourceManager::LightingColorShader())), Matrix4f::Scale(50, 1, 50)));


			GameObject* camera0 = AddToScene(GameObject::Instantiate("Camera0", -25, 10, 25))
				->AddComponent(new Camera());
			camera0->transform().LocalRotation() = Quaternion::LookAt(Vector3f(1, 0, -1).Normalize());
			camera0->transform().Rotate(-PI / 5.0f, Vector3f::Right(), Space::Local);

			GameObject* camera1 = AddToScene(GameObject::Instantiate("Camera1", 25, 10, 25))
				->AddComponent(new Camera());
			camera1->transform().LocalRotation() = Quaternion::LookAt(Vector3f(-1, 0, -1).Normalize());
			camera1->transform().Rotate(-PI / 5.0f, Vector3f::Right(), Space::Local);

			GameObject* camera2 = AddToScene(GameObject::Instantiate("Camera2", 25, 10, -25))
				->AddComponent(new Camera());
			camera2->transform().LocalRotation() = Quaternion::LookAt(Vector3f(-1, 0, 1).Normalize());
			camera2->transform().Rotate(-PI / 5.0f, Vector3f::Right(), Space::Local);

			GameObject* camera3 = AddToScene(GameObject::Instantiate("Camera3", -25, 10, -25))
				->AddComponent(new Camera());
			camera3->transform().LocalRotation() = Quaternion::LookAt(Vector3f(1, 0, 1).Normalize());
			camera3->transform().Rotate(-PI / 5.0f, Vector3f::Right(), Space::Local);

			cam0->SetCamera(camera0);
			cam1->SetCamera(camera1);
			cam2->SetCamera(camera2);
			cam3->SetCamera(camera3);

			main["PlayerOrientation"].AddComponent(new Follow(&main["Player"], 100));
			main.GetActiveCamera().MakeChildOf(&main["PlayerOrientation"]);

			Layer& ui = scene.CreateLayer("UI");
			scene.SetCurrentLayer("UI");

			AddToScene(GameObject::Instantiate("Camera0Frame", WindowWidth() / 4, WindowHeight() / 4, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", cam0)), Matrix4f::Scale(WindowWidth() / 2, WindowHeight() / 2, 1)));

			AddToScene(GameObject::Instantiate("Camera1Frame", WindowWidth() / 4 * 3, WindowHeight() / 4, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", cam1)), Matrix4f::Scale(WindowWidth() / 2, WindowHeight() / 2, 1)));

			AddToScene(GameObject::Instantiate("Camera2Frame", WindowWidth() / 4 * 3, WindowHeight() / 4 * 3, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", cam2)), Matrix4f::Scale(WindowWidth() / 2, WindowHeight() / 2, 1)));

			AddToScene(GameObject::Instantiate("Camera3Frame", WindowWidth() / 4, WindowHeight() / 4 * 3, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", cam3)), Matrix4f::Scale(WindowWidth() / 2, WindowHeight() / 2, 1)));

			ui.SetActiveCamera(AddToScene(GameObject::Instantiate("Canvas", 0, 0, 10))
				->AddComponent(new Camera(Projection::Orthographic)));

			scene.SetCurrentLayer("Main");
			
			GraphicsPipeline g;
			g.Renderer = new ForwardRenderer;
			g.Schedule = new RenderSchedule;

			g.Schedule->AddRenderPass(new RenderPass("Camera0", cam0));
			g.Schedule->AddRenderPass(new RenderPass("Camera0", cam1));
			g.Schedule->AddRenderPass(new RenderPass("Camera0", cam2));
			g.Schedule->AddRenderPass(new RenderPass("Camera0", cam3));

			g.Schedule->AddRenderPass(new RenderPass("Default", LayerMask("UI")));
			Graphics::AddGraphicsPipeline(g);
		}

		void Tick() override
		{
			
		}

		void Update() override
		{
			Graphics::CurrentContext().SetTitle(std::to_string((int)Time::AvgFPS()));

			Camera& camera = SceneManager::Instance().CurrentScene()["Main"].GetActiveCamera().GetComponent<Camera>();
			Transform& player = SceneManager::Instance().CurrentScene()["Main"]["Player"].transform();

			Vector3f position = Input::MousePosition();
			position.z = camera.Owner()->transform().LocalPosition().z;
			Vector3f direction = camera.ScreenToWorldPoint(position) - player.Position();
			direction.y = 0.0f;
			direction = direction.Normalize();
			SceneManager::Instance().CurrentScene()["Main"]["Player"].transform().LocalRotation() = Quaternion::LookAt(direction);

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