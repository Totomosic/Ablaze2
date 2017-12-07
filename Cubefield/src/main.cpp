#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::VM;

class Game : public Application
{
private:
	Window* m_Window;
	Scene* scene;
	Shader* shader;

	GameObject* cubePrefab;

public:
	void Init() override
	{

		m_Window = new Window(1280, 720, "Ablaze: 60", Color::CornflowerBlue());
		Graphics::Initialise(m_Window);
		Graphics::EnableCull();
		Graphics::EnableDepthTest();

		scene = &SceneManager::Instance().CreateScene();
		Layer& world = scene->CreateLayer("World");
		Layer& ui = scene->CreateLayer("UI");
		Layer& backgroundLayer = scene->CreateLayer("Background");

		Systems::Lighting().AddShader(ResourceManager::Instance().LoadShader("res/base.shader"));
		shader = ResourceManager::Instance().LoadShader("res/cube.shader").get();

		scene->SetCurrentLayer("Background");

		GameObject* backgroundCamera = GameObject::Instantiate("BackgroundCamera", 0, 0, 0);
		backgroundCamera->AddComponent(new Camera(Projection::Orthographic));

		GameObject* background = GameObject::Instantiate("Background", WindowWidth() / 2, WindowHeight() / 2, -999);
		background->AddComponent(new Mesh(ResourceManager::Instance().CreateRectangle(Color::White()), std::make_shared<Material<Texture2D>>(Color::White(), ResourceManager::Instance().DefaultTextureShader(), "Tex0", "res/background.png")));
		background->transform().LocalScale() = Maths::Vec3(WindowWidth(), WindowHeight(), 1);

		scene->SetCurrentLayer("World");

		GameObject* worldCamera = GameObject::Instantiate("WorldCamera", 0, 0, 5);
		worldCamera->AddComponent<Camera>();

		GameObject* floor = GameObject::Instantiate("Floor", 0, -7, -10);
		floor->AddComponent(new Mesh(ResourceManager::Instance().CreatePlane(), std::make_shared<Material<Texture2D>>(Color::White(), ResourceManager::Instance().LightingColorShader())));
		floor->transform().LocalScale() = Maths::Vec3(300, 1, 1500);

		GameObject* player = GameObject::Instantiate("Player", 0, -5, -10);
		player->AddComponent(new Mesh(ResourceManager::Instance().CreateCuboid(), std::make_shared<Material<Texture2D>>(Color::Green(), ResourceManager::Instance().LightingColorShader())));
		player->AddComponent(new RigidBody(false));

		GameObject* sun = GameObject::Instantiate("Sun", 0, 100, -10);
		sun->AddComponent<Light>();

		world.SetActiveCamera(worldCamera);
		backgroundLayer.SetActiveCamera(backgroundCamera);

		scene->SetCurrentLayer(nullptr);
		cubePrefab = GameObject::Instantiate("CubePrefab");
		cubePrefab->AddComponent(new RigidBody(false));
		cubePrefab->AddComponent(new Mesh(ResourceManager::Instance().CreateCuboid(), std::make_shared<Material<Texture2D>>(Color::Red(), ResourceManager::Instance().DefaultColorShader())));
		cubePrefab->transform().LocalScale() = Maths::Vec3(3);

		scene->SetCurrentLayer("World");

		Time::CreateNewTimer(0.1, METHOD_0(Game::CreateBlock));

		GraphicsPipeline g;
		g.Renderer = new ForwardRenderer;
		g.Schedule = new RenderSchedule;
		g.Schedule->AddRenderPass(new RenderPass("Default"));
		Graphics::AddGraphicsPipeline(g);

	}

	void CreateBlock()
	{
		static float speed = 1;
		GameObject* block = GameObject::Instantiate("Block", cubePrefab, Random::NextFloat(-150, 150), -4, -1000);
		block->transform().LocalScale() = Maths::Vec3(3);
		block->GetComponent<RigidBody>().Velocity().z = 200 + speed;
		speed *= 1.001f;
	}

	void Tick() override
	{

	}

	void Update() override
	{
		m_Window->SetTitle("Ablaze: " + std::to_string((int)Time::AvgFPS()));

		GameObject* camera = SceneManager::Instance().CurrentScene().GetLayer("World").GetActiveCamera();
		Transform& cTransform = camera->transform();

		GameObject& player = SceneManager::Instance().CurrentScene().GetLayer("World").GetNamedGameObject("Player");
		Transform& transform = player.transform();
		RigidBody& rb = player.GetComponent<RigidBody>();
		float speed = 100;

		cTransform.LocalRotation() = Maths::Quaternion::FromAngleAxis(0, Maths::Vec3(0, 0, 1));
		if (Input::KeyDown(Keycode::D))
		{
			rb.Acceleration() += transform.Right() * speed;
		}
		else if (Input::KeyDown(Keycode::A))
		{
			rb.Acceleration() += -transform.Right() * speed;
		}
		else
		{

		}

		Application::Update();
		SceneManager::Instance().CurrentScene().GetLayer("World").GetActiveCamera()->transform().LocalPosition().x = transform.Position().x;

		std::vector<GameObject*> objects = GameObject::GetAllWith<Transform>();
		for (GameObject* object : objects)
		{
			if (object->transform().Position().z > 0 && !object->HasComponent<Camera>())
			{
				object->Destroy();
			}
		}
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