#include "Ablaze.h"

using namespace Ablaze;

class Game : public Application
{
private:
	Window* m_Window;

public:
	void Init() override
	{
		m_Window = BuildWindow(1280, 720, "Ablaze: 60", Color::White());
		m_Window->SetIcon("normal.png");
		Graphics::Initialise(m_Window);

		Resource<Shader> s = ResourceManager::Library().LoadShader("base_v.glsl", "base_f.glsl");
		s.Increment();
		s->Bind();

		Resource<Texture2D> tex = ResourceManager::Library().LoadTexture2D("image.png", MipmapMode::Enabled);
		Resource<Texture2D> tex2 = ResourceManager::Library().LoadTexture2D("normal.png");

		Material mat(Color::White(), s, "Tex0", tex);
		Resource<Model> model = ResourceManager::Library().CreateRectangle(1, 1, Color::White());
		Mesh mesh(model, mat);

		Material mat2(Color::White(), s, "Tex0", tex2);
		Resource<Model> model2 = ResourceManager::Library().CreateRectangle(0.5f, 0.5f);
		Mesh mesh2(model2, mat2);

		Scene& scene = SceneManager::Instance().CreateScene();
		scene.CreateLayer("World", new Camera());

		Entity* entity = new Entity(mesh);
		Entity* entity2 = new Entity(mesh2);

	}

	void Tick() override
	{
		
	}

	void Update() override
	{
		m_Window->SetTitle("Ablaze: " + std::to_string((int)Time::AvgFPS()));
	}

	void Render() override
	{
		Application::Render();

		for (auto entity : SceneManager::Instance().CurrentScene().CurrentLayer().GetEntities())
		{
			RenderMesh(entity->GetMesh());
		}

		UpdateDisplay();
	}

	void RenderMesh(Mesh& mesh)
	{
		for (int i = 0; i < mesh.ModelCount(); i++)
		{
			const ModelSet& modelSet = mesh.GetModelSet(i);
			modelSet.material.GetShader()->Bind();
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