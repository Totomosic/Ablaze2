#include "Ablaze.h"

#include "Components\PlayerController.h"
#include "Components\Chatbox.h"
#include "Components\Pathing.h"

using namespace Ablaze;
using namespace Ablaze::VM;
using namespace Ablaze::Maths;

class Game : public Application
{
public:

public:
	void Init() override
	{
		Window* window = new Window(1280, 720, "AblazeScape", Color::CornflowerBlue());
		Graphics::Initialise(window);
		Graphics::EnableCull();

		SceneManager::Instance().CreateScene();
		SceneManager::Instance().CurrentScene().CreateLayer("World");
		SceneManager::Instance().CurrentScene().SetCurrentLayer(0);

		GameObject* player = GameObject::Instantiate("Player", 0, 0, 0);
		player->AddComponent(new Mesh(ResourceManager::Instance().Cube(), std::make_shared<Material<>>(Color::White(), ResourceManager::Instance().LightingTextureShader(), "Tex0", ResourceManager::Instance().LoadTexture2D("res/canyonTerrain.png"))));
		player->AddComponent(new BoxCollider(OBB(Maths::Vector3f(1, 1, 1))));
		player->AddComponent(new Pathing(5));
		GameObject* playerOrientation = GameObject::Instantiate("PlayerOrientation", nullptr, player, 0, 0, 0);
		playerOrientation->transform().Rotate(-Maths::PI / 2.0, Vector3f::Right());

		GameObject* terrain = GameObject::Instantiate("Terrain", 0, -0.5f, 0);
		terrain->AddComponent(new Mesh(ResourceManager::Instance().Plane(), std::make_shared<Material<>>(Color::Green(), ResourceManager::Instance().LightingColorShader()), Matrix4d::Scale(150)));
		terrain->AddComponent(new BoxCollider(OBB(Maths::Vector3f(150, 0, 150))));

		GameObject* camera = GameObject::Instantiate("Camera", nullptr, playerOrientation, 0, 0, 100);
		camera->AddComponent<Camera>();

		GameObject* sun = GameObject::Instantiate("Sun", 0, 100, 0);
		sun->AddComponent<Light>();

		SceneManager::Instance().CurrentScene().CurrentLayer().SetActiveCamera(camera);

		SceneManager::Instance().CurrentScene().CreateLayer("UI");
		SceneManager::Instance().CurrentScene().SetCurrentLayer("UI");

		GameObject* chatbox = GameObject::Instantiate("Chatbox", 255, 105, 0);
		chatbox->AddComponent(new Mesh(ResourceManager::Instance().Square(), std::make_shared<Material<>>(Color(240, 240, 230), ResourceManager::Instance().DefaultColorShader()), Maths::Matrix4d::Scale(500, 200, 1)));
		GameObject* chatboxBorder = GameObject::Instantiate("ChatboxBorder", chatbox, chatbox, 0, 0, -1);
		chatboxBorder->mesh().GetMaterial(0) = std::make_shared<Material<>>(Color::Red(), ResourceManager::Instance().DefaultColorShader());
		chatboxBorder->mesh().GetTransform(0) = Maths::Matrix4d::Scale(510, 210, 1);
		GameObject* chatbar = GameObject::Instantiate("Chatbar", chatbox, chatbox, 0, -90, 1);
		chatbar->mesh().GetMaterial(0) = std::make_shared<Material<>>(Color(220, 200, 220), ResourceManager::Instance().DefaultColorShader());
		chatbar->mesh().GetTransform(0) = Maths::Matrix4d::Scale(500, 20, 1);

		chatbox->AddComponent(new Chatbox(500, 200, ResourceManager::Instance().LoadFont("res/Arial.ttf", 16)));

		GameObject* fpsText = GameObject::Instantiate("FPSText", 5, WindowHeight() - 5, 1);
		fpsText->AddComponent(new Text("fps ", ResourceManager::Instance().LoadFont("res/Roboto-Black.ttf", 24), Color::Black(), TextAlignmentH::Left, TextAlignmentV::Top));

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

	void Tick() override
	{

	}

	void Update() override
	{
		GameObject& camera = *SceneManager::Instance().CurrentScene()["World"].GetActiveCamera();
		Transform& transform = SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("PlayerOrientation").transform();
		Chatbox& chatbox = SceneManager::Instance().CurrentScene()["UI"].GetNamedGameObject("Chatbox").GetComponent<Chatbox>();

		SceneManager::Instance().CurrentScene()["UI"].GetNamedGameObject("FPSText").GetComponent<Text>().SetText("fps " + std::to_string((int)Time::AvgFPS()));

		if (Input::MouseButtonDown(MouseButton::Right))
		{
			RaycastHit hit = Physics::Raycast(camera.GetComponent<Camera>().ScreenToWorldRay(Input::MousePosition(Origin::BottomLeft)), LayerMask("World"));
			if (hit.DidHit)
			{
				chatbox.Post(hit.GameObjects[0]->Tag());
				chatbox.Post(hit.HitLocations[0].ToString());
				SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("Player").GetComponent<Pathing>().SetTarget(Vector3f(hit.HitLocations[0].x, 0, hit.HitLocations[0].z));
			}
		}

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