#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::VM;

class Game : public Application
{
private:
	Window* m_Window;
	bool m_FPS;

public:
	void Init() override
	{
		m_Window = new Window(1280, 720, "Ablaze: 60", Color::CornflowerBlue());
		m_Window->SetIcon("normal.png");
		Graphics::Initialise(m_Window);
		Graphics::EnableCull();

		Resource<Shader> s = ResourceManager::Library().LoadShader("base.shader");
		Resource<Shader> basic = ResourceManager::Library().LoadShader("default.shader");

		Scene& scene = SceneManager::Instance().CreateScene();
		Layer& world = scene.CreateLayer("World", new Camera(Projection::Perspective));
		Layer& ui = scene.CreateLayer("UI", new Camera(Projection::Orthographic));

		world.AddEntity(new Terrain(500, 500, 512, 512, Material(Color::White(), s, "Tex0", "image.png")), "Terrain");
		world.CreateEntity(0, 0, 0, Mesh(ResourceManager::Library().CreatePlane(500, 500), Material(Color(20, 50, 180, 200), basic)));
		ui.CreateEntity(m_Window->GetWidth() / 2, m_Window->GetHeight() / 2, -5, Mesh(ResourceManager::Library().CreateRectangle(50, 50), Material(Color::White(), basic)));

		HeightmapFunction func("defaultTerrain.png", -50, 50);

		TerrainData& data = world.GetNamedEntity<Terrain>("Terrain").BeginEditing();
		data.SetRegion(0, 0, 512, 512, func);
		world.GetNamedEntity<Terrain>("Terrain").EndEditing(data);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}

	void Tick() override
	{

	}

	void Update() override
	{
		m_Window->SetTitle("Ablaze: " + std::to_string((int)Time::AvgFPS()));
		
		float speed = 10;
		Camera* camera = SceneManager::Instance().CurrentScene().GetLayer("World").GetActiveCamera();
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

		if (Input::KeyDown(Keycode::W))
		{
			camera->Velocity() += camera->GetTransform().Forward() * speed;
		}
		else if (Input::KeyDown(Keycode::S))
		{
			camera->Velocity() += camera->GetTransform().Forward() * -speed;
		}

		if (Input::KeyDown(Keycode::D))
		{
			camera->Velocity() += camera->GetTransform().Right() * speed;
		}
		else if (Input::KeyDown(Keycode::A))
		{
			camera->Velocity() += camera->GetTransform().Right() * -speed;
		}

		if (Input::KeyDown(Keycode::Left))
		{
			camera->GetTransform().Rotate(45 * Time::DeltaTime(), Maths::Vec3(0, 1, 0), Space::World, Angle::Degrees);
		}
		if (Input::KeyDown(Keycode::Right))
		{
			camera->GetTransform().Rotate(-45 * Time::DeltaTime(), Maths::Vec3(0, 1, 0), Space::World, Angle::Degrees);
		}
		if (Input::KeyDown(Keycode::Up))
		{
			camera->GetTransform().Rotate(45 * Time::DeltaTime(), Maths::Vec3(1, 0, 0), Space::Local, Angle::Degrees);
		}
		if (Input::KeyDown(Keycode::Down))
		{
			camera->GetTransform().Rotate(-45 * Time::DeltaTime(), Maths::Vec3(1, 0, 0), Space::Local, Angle::Degrees);
		}

		if (m_FPS)
		{
			camera->Rotate(Input::RelMousePosition().x * 0.2f, Maths::Vec3(0, 1, 0), Space::World, Angle::Degrees);
			camera->Rotate(-Input::RelMousePosition().y * 0.2f, Maths::Vec3(1, 0, 0), Space::Local, Angle::Degrees);
		}

		SceneManager::Instance().CurrentScene().Update(Time::ElapsedTime());
		camera->Velocity() = Maths::Vec3();
	}

	void Render() override
	{

		Application::Render();

		if (SceneManager::Instance().HasScene())
		{
			for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers())
			{
				for (Entity* entity : layer->GetEntities())
				{
					RenderMesh(*entity, entity->GetMesh(), layer->GetActiveCamera());
				}
			}
		}

		UpdateDisplay();

	}

	void RenderMesh(Entity& entity, Mesh& mesh, Camera* camera)
	{
		for (int i = 0; i < mesh.ModelCount(); i++)
		{
			const ModelSet& modelSet = mesh.GetModelSet(i);
			Resource<Shader> shader = modelSet.material.GetShader();
			shader->Bind();
			shader->SetUniform("modelMatrix", modelSet.transform * entity.GetTransform().ToMatrix());
			shader->SetUniform("viewMatrix", camera->ViewMatrix());
			shader->SetUniform("projectionMatrix", camera->ProjectionMatrix());
			shader->SetUniform("color", modelSet.material.BaseColor());
			modelSet.material.Textures().BindAll(modelSet.material.GetShader());
			modelSet.material.RenderSettings().Apply();
			VertexArray* vao = modelSet.model->GetVertexArray();
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