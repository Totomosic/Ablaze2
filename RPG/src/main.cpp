#include "Ablaze.h"

#include "Components\PlayerController.h"

using namespace Ablaze;
using namespace Ablaze::VM;
using namespace Ablaze::Maths;

class Game : public Application
{
public:

public:
	void Init() override
	{
		Window* window = new Window(1280, 720, "AblazeScape: ", Color::CornflowerBlue());
		Graphics::Initialise(window);
		Graphics::EnableCull();

		SceneManager::Instance().CreateScene();
		SceneManager::Instance().CurrentScene().CreateLayer("World");
		SceneManager::Instance().CurrentScene().SetCurrentLayer(0);

		GameObject* player = GameObject::Instantiate("Player", 0, 0, 0);
		player->AddComponent(new Mesh(ResourceManager::Instance().Cube(), std::make_shared<Material<>>(Color::White(), ResourceManager::Instance().LightingTextureShader(), "Tex0", ResourceManager::Instance().LoadTexture2D("res/canyonTerrain.png"))));
		player->AddComponent(new PlayerController(3));
		GameObject* playerOrientation = GameObject::Instantiate("PlayerOrientation", nullptr, player, 0, 0, 0);

		GameObject* terrain = GameObject::Instantiate("Terrain", 0, -0.5f, 0);
		terrain->AddComponent(new Mesh(ResourceManager::Instance().Plane(), std::make_shared<Material<>>(Color::Green(), ResourceManager::Instance().LightingColorShader())));
		terrain->transform().LocalScale() = Maths::Vector3f(15, 1, 15);

		GameObject* camera = GameObject::Instantiate("Camera", nullptr, playerOrientation, 0, 0, 10);
		camera->AddComponent<Camera>();

		GameObject* sun = GameObject::Instantiate("Sun", 0, 100, 0);
		sun->AddComponent<Light>();

		SceneManager::Instance().CurrentScene().CurrentLayer().SetActiveCamera(camera);

		SceneManager::Instance().CurrentScene().CreateLayer("UI");
		SceneManager::Instance().CurrentScene().SetCurrentLayer("UI");

		GameObject* canvas = GameObject::Instantiate("Canvas", 0, 0, 100);
		canvas->AddComponent(new Camera(Projection::Orthographic));

		SceneManager::Instance().CurrentScene().CurrentLayer().SetActiveCamera(canvas);

		// Render Setup
		GraphicsPipeline g;
		g.Renderer = new ForwardRenderer;
		g.Schedule = new RenderSchedule;
		g.Schedule->AddRenderPass(new RenderPass("Default"));
		Graphics::AddGraphicsPipeline(g);
	}

	void Update() override
	{
		Graphics::CurrentContext().SetTitle("AblazeScape: " + std::to_string((int)Time::AvgFPS()));

		GameObject& camera = *SceneManager::Instance().CurrentScene()["World"].GetActiveCamera();
		Transform& transform = SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("PlayerOrientation").transform();

		if (Input::KeyDown(Keycode::Down))
		{
			transform.Rotate(Maths::PI / 2 * Time::DeltaTime(), Maths::Vector3f(1, 0, 0), Space::Local);
		}
		if (Input::KeyDown(Keycode::Up))
		{
			transform.Rotate(-Maths::PI / 2 * Time::DeltaTime(), Maths::Vector3f(1, 0, 0), Space::Local);
		}
		if (Input::KeyDown(Keycode::Right))
		{
			transform.Rotate(Maths::PI / 2 * Time::DeltaTime(), Maths::Vector3f(0, 1, 0), Space::World);
		}
		if (Input::KeyDown(Keycode::Left))
		{
			transform.Rotate(-Maths::PI / 2 * Time::DeltaTime(), Maths::Vector3f(0, 1, 0), Space::World);
		}
		camera.transform().LocalPosition() += Maths::Vector3f::Forward() * Input::RelMouseScroll().y;

		Application::Update();
	}

	void Render() override
	{
		Application::Render();

		Graphics::Clear();
		Graphics::RenderScene();
		Graphics::Present();
	}

};

int main()
{
	Game g;
	g.Start();
	return 0;
}