#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::VM;

class Game : public Application
{
private:
	Window* m_Window;
	bool m_FPS = false;
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

		Resource<Model> cube = ResourceManager::Library().CreateCuboid(1, 1, 1);

		GameObject* camera = new GameObject;
		camera->Components().AddComponent(new Transform(Maths::Vec3(0, 5, 5), Maths::Quaternion::FromAngleAxis(-Maths::PI / 4.0, Maths::Vec3(1, 0, 0))));
		camera->Components().AddComponent(new Camera());

		GameObject* obj = new GameObject;
		obj->Components().AddComponent(new Transform());
		obj->Components().AddComponent(new Mesh(cube, Material(Color::White(), "base.shader", "Tex0", "border.png")));

		world.SetActiveCamera(camera);
		world.AddGameObject(camera);
		world.AddGameObject(obj, "Player");

	}

	void Tick() override
	{

	}

	void Update() override
	{
		m_Window->SetTitle("Ablaze: " + std::to_string((int)Time::AvgFPS()));

		GameObject& camera = *scene->GetLayer("World").GetActiveCamera();
		Transform& t = *camera.Components().GetComponent<Transform>();
		float speed = 3;

		if (Input::KeyDown(Keycode::D))
		{
			t.Position() += t.Right() * speed * Time::DeltaTime();
		}
		if (Input::KeyDown(Keycode::A))
		{
			t.Position() -= t.Right() * speed * Time::DeltaTime();
		}
		if (Input::KeyDown(Keycode::W))
		{
			t.Position() += t.Forward() * speed * Time::DeltaTime();
		}
		if (Input::KeyDown(Keycode::S))
		{
			t.Position() -= t.Forward() * speed * Time::DeltaTime();
		}

		if (Input::KeyPressed(Keycode::C))
		{
			m_FPS = !m_FPS;
			if (m_FPS)
			{
				Input::CaptureCursor();
			}
			else
			{
				Input::ReleaseCursor();
			}
		}
		if (m_FPS)
		{
			t.Rotate(Input::RelMousePosition().x * 0.2f, Maths::Vec3(0, 1, 0), Space::World, Angle::Degrees);
			t.Rotate(-Input::RelMousePosition().y * 0.2f, Maths::Vec3(1, 0, 0), Space::Local, Angle::Degrees);
		}

	}

	void Render() override
	{
		Application::Render();

		for (GameObject* object : scene->GetLayer("World").GameObjects())
		{
			if (object->Components().HasComponent<Transform>() && object->Components().HasComponent<Mesh>())
			{
				RenderMesh(*object->Components().GetComponent<Transform>(), *object->Components().GetComponent<Mesh>(), scene->GetLayer("World").GetActiveCamera());
			}
		}

		UpdateDisplay();
	}

	void RenderMesh(const Transform& transform, const Mesh& mesh, GameObject* camera)
	{
		Camera* camComp = camera->Components().GetComponent<Camera>();
		Transform* camT = camera->Components().GetComponent<Transform>();
		for (const ModelSet& set : mesh.GetModelSets())
		{
			const Material& mat = set.material;
			Resource<Model> model = set.model;
			Resource<Shader> shader = mat.GetShader();
			shader->Bind();
			shader->SetUniform("modelMatrix", set.transform * transform.ToMatrix());
			shader->SetUniform("viewMatrix", camT->ToMatrix().Inverse());
			shader->SetUniform("projectionMatrix", camComp->ProjectionMatrix());
			shader->SetUniform("color", mat.BaseColor());
			mat.RenderSettings().Apply();
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