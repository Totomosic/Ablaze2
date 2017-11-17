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

		Systems::Lighting().AddShader(ResourceManager::Library().LoadShader("res/base.shader"));
		shader = *ResourceManager::Library().LoadShader("res/cube.shader");

		scene->SetCurrentLayer("Background");

		GameObject* backgroundCamera = GameObject::Instantiate(0, 0, 0);
		backgroundCamera->AddComponent(new Camera(Projection::Orthographic));

		GameObject* background = GameObject::Instantiate(WindowWidth() / 2, WindowHeight() / 2, -999);
		background->AddComponent(new Mesh(ResourceManager::Library().CreateRectangle(WindowWidth(), WindowHeight(), Color::White()), Material<Texture2D>(Color::White(), ResourceManager::Library().DefaultTextureShader(), "Tex0", "res/background.png")));

		scene->SetCurrentLayer("World");

		GameObject* worldCamera = GameObject::Instantiate(0, 0, 5);
		worldCamera->AddComponent<Camera>();

		GameObject* floor = GameObject::Instantiate(0, -7, -30);
		floor->AddComponent(new Mesh(ResourceManager::Library().CreatePlane(300, 1500), Material<Texture2D>(Color::White(), ResourceManager::Library().LightingColorShader())));

		GameObject* player = GameObject::Instantiate(0, -5, -10);
		player->AddComponent(new Mesh(ResourceManager::Library().CreateCuboid(1, 1, 1), Material<Texture2D>(Color::Green(), ResourceManager::Library().LightingColorShader())));
		player->AddComponent(new RigidBody(false));
		player->SetTag("Player");

		GameObject* sun = GameObject::Instantiate();
		sun->AddComponent(new Transform(Maths::Vec3(0, 100, -10)));
		sun->AddComponent<Light>();

		scene->SetCurrentLayer(nullptr);
		cubePrefab = GameObject::Instantiate();
		cubePrefab->AddComponent(new RigidBody(false));
		cubePrefab->AddComponent(new Mesh(ResourceManager::Library().CreateCuboid(3, 3, 3), Material<Texture2D>(Color::Red(), ResourceManager::Library().DefaultColorShader())));

		world.SetActiveCamera(worldCamera);
		backgroundLayer.SetActiveCamera(backgroundCamera);

		scene->SetCurrentLayer("World");

		Time::CreateNewTimer(0.1, METHOD_0(Game::CreateBlock));

	}

	void CreateBlock()
	{
		static float speed = 1;
		GameObject* block = GameObject::Instantiate(cubePrefab, Random::NextFloat(-150, 150), -4, -1000);
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

		for (GameObject* object : GameObject::GetAllWith<Transform, Mesh>())
		{
			RenderMesh(object->transform(), object->mesh(), object->GetLayer()->GetActiveCamera());
		}

		UpdateDisplay();
	}

	void RenderMesh(const Transform& transform, const Mesh& mesh, GameObject* camera)
	{
		Camera& camComp = camera->GetComponent<Camera>();
		Transform& camT = camera->GetComponent<Transform>();
		for (const ModelSet& set : mesh.GetModelSets())
		{
			const MaterialBase& mat = *set.material;
			const Resource<Model>& model = set.model;
			const Resource<Shader>& shader = mat.ActiveShader();
			shader->Bind();
			shader->SetUniform("modelMatrix", set.transform * transform.ToMatrix());
			shader->SetUniform("viewMatrix", camT.ToMatrix().Inverse());
			shader->SetUniform("projectionMatrix", camComp.ProjectionMatrix());
			shader->SetUniform("color", mat.BaseColor());
			mat.Apply();
			VertexArray* vao = model->GetVertexArray();
			vao->Bind();
			glDrawElements((GLenum)vao->GetRenderMode(), vao->RenderCount(), GL_UNSIGNED_INT, nullptr);
		}
	}

};

int main()
{
	Game g;
	g.Start();
	return 0;
}