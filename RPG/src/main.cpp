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
	RenderTexture* waterReflect;

public:
	void Init() override
	{
		Window* window = new Window(1280, 720, "AblazeScape", Color::CornflowerBlue());
		Graphics::Initialise(window);
		Graphics::EnableCull();

		AB_INFO(Filesystem::WorkingDirectory());

		glEnable(GL_CLIP_PLANE0);

		Shader* waterShader = Shader::FromFile("res/Water.shader");
		Systems::Lighting().AddShader(waterShader);

		SetTexture2D("WaterDUDV", new Texture2D("res/Water/waterDUDV.png", MipmapMode::Enabled));
		SetTexture2D("WaterNormal", new Texture2D("res/Water/normal.png", MipmapMode::Enabled));
		waterReflect = new RenderTexture(WindowWidth(), WindowHeight(), LayerMask("World"));
		RenderTexture* waterRefract = new RenderTexture(WindowWidth(), WindowHeight(), LayerMask("World"));
		waterReflect->RenderTarget().SetClearColor(Color::CornflowerBlue());
		waterRefract->RenderTarget().SetClearColor(Color::CornflowerBlue());

		Scene& scene = SceneManager::Instance().CreateScene();
		Layer& worldLayer = scene.CreateLayer("World");
		scene.SetCurrentLayer("World");

		SetTexture2D("CanyonTerrain", new Texture2D("res/canyonTerrain.png", MipmapMode::Enabled));

		GameObject* player = AddToScene(GameObject::Instantiate("Player", 0, 0, 0))
			->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Cube(), Material(Color::White(), ResourceManager::LightingTextureShader(), "Tex0", GetTexture2D("CanyonTerrain")))))
			->AddComponent(new BoxCollider(OBB(Maths::Vector3f(1, 1, 1))))
			->AddComponent(new Pathing(50));
		GameObject* playerOrientation = AddToScene(GameObject::Instantiate("PlayerOrientation", 0, 0, 0));
		playerOrientation->MakeChildOf(player);
		playerOrientation->transform().Rotate(-Maths::PI / 2.0, Vector3f::Right());

		GameObject* terrain = AddToScene(GameObject::Instantiate("Terrain", 0, 0, 0))
			->AddComponent(new Terrain(256, 256, 512, 512, Material(Color(50, 255, 140), ResourceManager::LightingColorShader())));

		TerrainData& data = terrain->GetComponent<Terrain>().BeginEditing();
		data.SetRegion(0, 0, 512, 512, 0, 0, HeightmapFunction("res/canyonTerrain.png", -25, 25));
		terrain->GetComponent<Terrain>().EndEditing(data);
		terrain->AddComponent(new BoxCollider(OBB(Maths::Vector3f(256, 0, 256))));

		GameObject* camera = AddToScene(GameObject::Instantiate("Camera", 0, 0, 100))
			->AddComponent<Camera>();
		camera->MakeChildOf(playerOrientation);

		AddToScene(GameObject::Instantiate("Light", 0, 100, 0))
			->AddComponent(new Light(LightType::Point, Color::White()));

		worldLayer.SetActiveCamera(camera);

		Layer& waterLayer = scene.CreateLayer("Water");
		scene.SetCurrentLayer("Water");

		Material waterMaterial = Material(Color(150, 180, 255), waterShader);
		waterMaterial.Textures().AddTexture("DUDV", GetTexture2D("WaterDUDV"));
		waterMaterial.Textures().AddTexture("Normal", GetTexture2D("WaterNormal"));
		waterMaterial.Textures().AddTexture("Reflection", waterReflect);
		waterMaterial.Textures().AddTexture("Refraction", waterRefract);
		waterMaterial.Uniforms().AddUniform("moveFactor", 0.0f);
		GameObject* water = AddToScene(GameObject::Instantiate("Water", 0, 0, 0))
			->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Plane(), waterMaterial), Maths::Matrix4d::Scale(512, 1, 512)));
		water->mesh().GetMesh(0)->GetMaterial().LightSettings().Shininess = 1.0f;
		water->mesh().GetMesh(0)->GetMaterial().LightSettings().ShineDamper = 10.0f;

		waterLayer.SetActiveCamera(camera);

		Layer& uiLayer = scene.CreateLayer("UI");
		scene.SetCurrentLayer("UI");

		GameObject* chatbox = AddToScene(GameObject::Instantiate("Chatbox", 255, 105, 0))
			->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color(240, 240, 230), ResourceManager::DefaultColorShader())), Maths::Matrix4d::Scale(500, 200, 1)));
		GameObject* chatboxBorder = AddToScene(GameObject::Instantiate("ChatboxBorder", 0, 0, -1))
			->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::Red(), ResourceManager::DefaultColorShader())), Maths::Matrix4d::Scale(510, 210, 1)));
		chatboxBorder->MakeChildOf(chatbox);
		GameObject* chatbar = AddToScene(GameObject::Instantiate("Chatbar", 0, -90, 1))
			->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color(220, 200, 220), ResourceManager::DefaultColorShader())), Maths::Matrix4d::Scale(500, 20, 1)));
		chatbar->MakeChildOf(chatbox);
		chatbox->AddComponent(new Chatbox(500, 200, SetFont("Arial16", new Font("res/Arial.ttf", 16))));

		GameObject* canvas = AddToScene(GameObject::Instantiate("Canvas", 0, 0, 10))
			->AddComponent(new Camera(Projection::Orthographic));

		texture = new RenderTexture(WindowWidth(), WindowHeight(), LayerMask("World", "Water"), CreateMode::Repeat, ColorBuffer::Color0);
		texture->RenderTarget().SetClearColor(Color::CornflowerBlue());

		SetFont("Roboto24", new Font("res/Roboto-Black.ttf", 24));

		GameObject* worldCanvas = AddToScene(GameObject::Instantiate("WorldCanvas", WindowWidth() / 2, WindowHeight() / 2, -10))
			->AddComponent(new MeshRenderer(new Mesh(Model::Rectangle(WindowWidth(), WindowHeight()), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", texture))));

		GameObject* fpsText = AddToScene(GameObject::Instantiate("FPSText", 5, WindowHeight() - 5, 1))
			->AddComponent(new Text("fps 60", GetFont("Roboto24"), Color::Black(), TextAlignmentH::Left, TextAlignmentV::Top));

		uiLayer.SetActiveCamera(canvas);

		// Render Setup
		GraphicsPipeline g;
		g.Renderer = new ForwardRenderer;
		g.Schedule = new RenderSchedule;
		g.Schedule->AddRenderPass(new RenderPass("World", texture));
		g.Schedule->AddRenderPass(new RenderPass("WaterReflect", waterReflect));
		g.Schedule->AddRenderPass(new RenderPass("WaterRefract", waterRefract));
		g.Schedule->AddRenderPass(new RenderPass("Display", LayerMask("UI")));
		g.Schedule->GetRenderPass(0)->Uniforms().AddUniform("ClippingPlane.Normal", Vector3f(0, 1, 0));
		g.Schedule->GetRenderPass(0)->Uniforms().AddUniform("ClippingPlane.Distance", 1000.0f);
		g.Schedule->GetRenderPass(1)->Uniforms().AddUniform("ClippingPlane.Normal", Vector3f(0, 1, 0));
		g.Schedule->GetRenderPass(1)->Uniforms().AddUniform("ClippingPlane.Distance", 0.0f);
		g.Schedule->GetRenderPass(2)->Uniforms().AddUniform("ClippingPlane.Normal", Vector3f(0, -1, 0));
		g.Schedule->GetRenderPass(2)->Uniforms().AddUniform("ClippingPlane.Distance", 1.0f);
		g.Schedule->GetRenderPass(3)->Uniforms().AddUniform("ClippingPlane.Normal", Vector3f(0, 1, 0));
		g.Schedule->GetRenderPass(3)->Uniforms().AddUniform("ClippingPlane.Distance", 1000.0f);
		Graphics::AddGraphicsPipeline(g);
	}

	void Tick() override
	{

	}

	void Update() override
	{
		GameObject& camera = SceneManager::Instance().CurrentScene()["World"].GetActiveCamera();
		Transform& transform = SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("PlayerOrientation").transform();
		Chatbox& chatbox = SceneManager::Instance().CurrentScene()["UI"].GetNamedGameObject("Chatbox").GetComponent<Chatbox>();

		Transform& player = SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("Player").transform();

		SceneManager::Instance().CurrentScene()["UI"].GetNamedGameObject("FPSText").GetComponent<Text>().SetText("fps " + std::to_string((int)Time::AvgFPS()));

		if (Input::MouseButtonDown(MouseButton::Right))
		{
			RaycastHit hit = Physics::Raycast(camera.GetComponent<Camera>().ScreenToWorldRay(Input::MousePosition(Origin::BottomLeft)), LayerMask("World"));
			if (hit.DidHit)
			{
				chatbox.Post(hit.GameObjects[0]->Tag());
				chatbox.Post(hit.HitLocations[0].ToString());
				SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("Player").GetComponent<Pathing>().SetTarget(Vector3f(hit.HitLocations[0].x, player.LocalPosition().y, hit.HitLocations[0].z));
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

		player.LocalPosition().y = max(SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("Terrain").GetComponent<Terrain>().Data().GetHeight(player.LocalPosition().x * 2 + 256, player.LocalPosition().z * 2 + 256), 0);
		if (Input::MouseButtonDown(MouseButton::Middle))
		{
			transform.Rotate(Input::RelMousePosition().x * Time::DeltaTime() * 0.5f, Vector3f::Up());
			transform.Rotate(-Input::RelMousePosition().y * Time::DeltaTime() * 0.5f, Vector3f::Right(), Space::Local);
		}

		((Uniform<float>*)SceneManager::Instance().CurrentScene()["Water"].GetNamedGameObject("Water").mesh().GetMesh(0)->GetMaterial().Uniforms().Get("moveFactor"))->Value() += Time::DeltaTime() * 0.1f;

		Application::Update();
	}

	void Render() override
	{
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