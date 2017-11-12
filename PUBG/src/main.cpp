#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::VM;

class Game : public Application
{
private:
	Window* m_Window;
	Scene* scene;

public:
	void Init() override
	{
		m_Window = new Window(1280, 720, "Ablaze: 60", Color::CornflowerBlue());
		m_Window->SetIcon("normal.png");
		Graphics::Initialise(m_Window);
		Graphics::EnableCull();

		scene = &SceneManager::Instance().CreateScene();
		Layer& world = scene->CreateLayer("World");
		Layer& ui = scene->CreateLayer("UI");
		Layer& backgroundLayer = scene->CreateLayer("Background");

		Systems::Lighting().AddShader(ResourceManager::Library().LoadShader("res/base.shader"));

		scene->SetCurrentLayer("Background");

		GameObject* backgroundCamera = GameObject::Instantiate(0, 0, 0);
		backgroundCamera->Components().AddComponent(new Camera(Projection::Orthographic));

		GameObject* background = GameObject::Instantiate(WindowWidth() / 2, WindowHeight() / 2, -999);
		background->AddComponent(new Mesh(ResourceManager::Library().CreateRectangle(WindowWidth(), WindowHeight(), Color::White()), Material(Color::White(), ResourceManager::Library().DefaultTextureShader(), "Tex0", "res/background.jpg")));

		scene->SetCurrentLayer("World");

		GameObject* worldCamera = GameObject::Instantiate(0, 0, 5);
		worldCamera->Components().AddComponent(new Camera(Projection::Perspective));

		GameObject* floor = GameObject::Instantiate(0, -7, -10);
		floor->AddComponent(new Mesh(ResourceManager::Library().CreateCuboid(20, 3, 5), Material(Color::White(), ResourceManager::Library().LightingColorShader())));

		GameObject* player = GameObject::Instantiate(0, -5, -10);
		player->AddComponent(new Mesh(ResourceManager::Library().CreateCuboid(1, 1, 1), Material(Color::Green(), ResourceManager::Library().LightingColorShader())));
		player->AddComponent(new RigidBody(false));
		player->SetTag("Player");

		GameObject* sun = GameObject::Instantiate();
		sun->AddComponent(new Transform(Maths::Vec3(0, 100, -10)));
		sun->AddComponent<Light>();

		world.SetActiveCamera(worldCamera);
		backgroundLayer.SetActiveCamera(backgroundCamera);

	}

	void Tick() override
	{

	}

	void Update() override
	{
		m_Window->SetTitle("Ablaze: " + std::to_string((int)Time::AvgFPS()));

		GameObject& player = SceneManager::Instance().CurrentScene().GetLayer("World").GetNamedGameObject("Player");
		Transform& transform = player.transform();
		RigidBody& rb = player.GetComponent<RigidBody>();
		float speed = 50;

		if (Input::KeyDown(Keycode::D))
		{
			rb.Acceleration() += transform.Right() * speed;
		}
		if (Input::KeyDown(Keycode::A))
		{
			rb.Acceleration() += transform.Right() * -speed;
		}

		Application::Update();

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
			const Material& mat = set.material;
			const Resource<Model>& model = set.model;
			const Resource<Shader>& shader = mat.GetShader();
			shader->Bind();
			shader->SetUniform("modelMatrix", set.transform * transform.ToMatrix());
			shader->SetUniform("viewMatrix", camT.ToMatrix().Inverse());
			shader->SetUniform("projectionMatrix", camComp.ProjectionMatrix());
			shader->SetUniform("color", mat.BaseColor());
			mat.RenderSettings().Apply();
			mat.Textures().BindAll(shader);
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