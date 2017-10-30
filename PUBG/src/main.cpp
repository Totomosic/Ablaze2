#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::VM;

class Game : public Application
{
private:
	Window* m_Window;

public:
	void Init() override
	{
		m_Window = new Window(1280, 720, "Ablaze: 60", Color::CornflowerBlue());
		m_Window->SetIcon("normal.png");
		Graphics::Initialise(m_Window);
		Graphics::EnableCull();

		Resource<Shader> s = ResourceManager::Library().LoadShader("base.shader");
		Resource<Texture2D> tex = ResourceManager::Library().LoadTexture2D("image.png", MipmapMode::Enabled);

		Material mat(Color::White(), s, "Tex0", tex);
		Resource<Model> model = ResourceManager::Library().CreateEllipse(5, 4, Color::White());
		Mesh mesh(model, mat);

		Scene& scene = SceneManager::Instance().CreateScene();
		scene.CreateLayer("World", new Camera(Projection::Perspective));

		Actor* entity = new Actor(0, 0, -5, mesh);

	}

	void Tick() override
	{

	}

	void Update() override
	{
		m_Window->SetTitle("Ablaze: " + std::to_string((int)Time::AvgFPS()));
		
		float speed = 3;
		Camera* camera = SceneManager::Instance().CurrentScene().CurrentLayer().GetCamera();
		if (Input::KeyDown(Keycode::W))
		{
			camera->Velocity().y = speed;
		}
		else if (Input::KeyDown(Keycode::S))
		{
			camera->Velocity().y = -speed;
		}
		else
		{
			camera->Velocity().y = 0;
		}

		if (Input::KeyDown(Keycode::D))
		{
			camera->Velocity().x = speed;
		}
		else if (Input::KeyDown(Keycode::A))
		{
			camera->Velocity().x = -speed;
		}
		else
		{
			camera->Velocity().x = 0;
		}
		SceneManager::Instance().CurrentScene().Update(Time::ElapsedTime());
	}

	void Render() override
	{

		Application::Render();

		if (SceneManager::Instance().HasScene())
		{
			for (Entity* entity : SceneManager::Instance().CurrentScene().CurrentLayer().GetEntities())
			{
				RenderMesh(entity, entity->GetMesh());
			}
		}

		UpdateDisplay();

	}

	void RenderMesh(Entity* entity, Mesh& mesh)
	{
		Camera* camera = SceneManager::Instance().CurrentScene().CurrentLayer().GetCamera();
		for (int i = 0; i < mesh.ModelCount(); i++)
		{
			const ModelSet& modelSet = mesh.GetModelSet(i);
			Resource<Shader> shader = modelSet.material.GetShader();
			shader->Bind();
			shader->SetUniform("modelMatrix", modelSet.transform * entity->GetTransform().ToMatrix());
			shader->SetUniform("viewMatrix", camera->ViewMatrix());
			shader->SetUniform("projectionMatrix", camera->ProjectionMatrix());
			modelSet.material.Textures().BindAll(modelSet.material.GetShader());
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