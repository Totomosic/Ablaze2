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
	RenderTexture* texture;

public:
	void Init() override
	{
		Window* window = new Window(1280, 720, "AblazeScape", Color::CornflowerBlue());
		Graphics::Initialise(window);
		Graphics::EnableCull();

		Scene& scene = SceneManager::Instance().CreateScene();
		Layer& worldLayer = scene.CreateLayer("World");
		scene.SetCurrentLayer("World");

		SetTexture2D("CanyonTerrain", new Texture2D("res/canyonTerrain.png", MipmapMode::Enabled));

		GameObject* player = GameObject::Instantiate("Player", 0, 0, 0);
		player->AddComponent(new Mesh(ResourceManager::Cube(), new Material<>(Color::White(), ResourceManager::LightingTextureShader(), "Tex0", GetTexture2D("CanyonTerrain"))));
		player->AddComponent(new BoxCollider(OBB(Maths::Vector3f(1, 1, 1))));
		player->AddComponent(new Pathing(500));
		GameObject* playerOrientation = GameObject::Instantiate("PlayerOrientation", nullptr, player, 0, 0, 0);
		playerOrientation->transform().Rotate(-Maths::PI / 2.0, Vector3f::Right());

		GameObject* terrain = GameObject::Instantiate("Terrain", 0, 0, 0);
		terrain->AddComponent(new Terrain(512, 512, 512, 512, new Material<>(Color::White(), ResourceManager::LightingColorShader())));
		TerrainData& data = terrain->GetComponent<Terrain>().BeginEditing();
		data.SetRegion(0, 0, 512, 512, HeightmapFunction("res/canyonTerrain.png", -50, 50));
		terrain->GetComponent<Terrain>().EndEditing(data);
		terrain->AddComponent(new BoxCollider(OBB(Maths::Vector3f(512, 0, 512))));

		GameObject* water = GameObject::Instantiate("Water", nullptr, terrain, 0, 0, 0);
		water->AddComponent(new Mesh(ResourceManager::Plane(), new Material<>(Color(100, 200, 255, 200), ResourceManager::LightingColorShader()), Maths::Matrix4d::Scale(512, 0, 512)));

		GameObject* camera = GameObject::Instantiate("Camera", nullptr, playerOrientation, 0, 0, 100);
		camera->AddComponent<Camera>();

		GameObject* sun = GameObject::Instantiate("Sun", 0, 500, 0);
		sun->AddComponent(new Mesh(ResourceManager::Cube(), new Material<>(Color::Yellow(), ResourceManager::DefaultColorShader())));
		sun->AddComponent<Light>();

		worldLayer.SetActiveCamera(camera);

		Layer& uiLayer = scene.CreateLayer("UI");
		scene.SetCurrentLayer("UI");

		GameObject* chatbox = GameObject::Instantiate("Chatbox", 255, 105, 0);
		chatbox->AddComponent(new Mesh(ResourceManager::Square(), new Material<>(Color(240, 240, 230), ResourceManager::DefaultColorShader()), Maths::Matrix4d::Scale(500, 200, 1)));
		GameObject* chatboxBorder = GameObject::Instantiate("ChatboxBorder", chatbox, chatbox, 0, 0, -1);
		chatboxBorder->mesh().SetMaterial(0, new Material<>(Color::Red(), ResourceManager::DefaultColorShader()));
		chatboxBorder->mesh().GetTransform(0) = Maths::Matrix4d::Scale(510, 210, 1);
		GameObject* chatbar = GameObject::Instantiate("Chatbar", chatbox, chatbox, 0, -90, 1);
		chatbar->mesh().SetMaterial(0, new Material<>(Color(220, 200, 220), ResourceManager::DefaultColorShader()));
		chatbar->mesh().GetTransform(0) = Maths::Matrix4d::Scale(500, 20, 1);

		chatbox->AddComponent(new Chatbox(500, 200, SetFont("Arial16", new Font("res/Arial.ttf", 16))));

		GameObject* fpsText = GameObject::Instantiate("FPSText", 5, WindowHeight() - 5, 1);
		fpsText->AddComponent(new Text("fps ", SetFont("Roboto24", new Font("res/Roboto-Black.ttf", 24)), Color::Black(), TextAlignmentH::Left, TextAlignmentV::Top));

		GameObject* canvas = GameObject::Instantiate("Canvas", 0, 0, 10);
		canvas->AddComponent(new Camera(Projection::Orthographic));

		uiLayer.SetActiveCamera(canvas);

		texture = new RenderTexture(WindowWidth(), WindowHeight(), LayerMask("World", "UI"));
		texture->RenderTarget().SetClearColor(Color::CornflowerBlue());

		Layer& displayLayer = scene.CreateLayer("Display");
		scene.SetCurrentLayer("Display");

		GameObject* displayCamera = GameObject::Instantiate("Camera", 0, 0, 10);
		displayCamera->AddComponent(new Camera(Projection::Orthographic));

		GameObject* screen = GameObject::Instantiate("Display", WindowWidth() / 2, WindowHeight() / 2, 0);
		screen->AddComponent(new Mesh(ResourceManager::Square(), new Material<RenderTexture>(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", texture)));
		screen->transform().LocalScale() = Maths::Vector3f(WindowWidth(), WindowHeight(), 1);

		displayLayer.SetActiveCamera(displayCamera);

		// Render Setup
		GraphicsPipeline g;
		g.Renderer = new ForwardRenderer;
		g.Schedule = new RenderSchedule;
		g.Schedule->AddRenderPass(new RenderPass("Default", texture));
		g.Schedule->AddRenderPass(new RenderPass("Display", LayerMask("Display")));
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