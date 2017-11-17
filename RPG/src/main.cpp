#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::VM;
using namespace Ablaze::Maths;

class Game : public Application
{
public:

public:
	void Init() override
	{
		Window* window = new Window(1280, 720, "RPG: ", Color::CornflowerBlue());
		Graphics::Initialise(window);

		SceneManager::Instance().CreateScene();
		SceneManager::Instance().CurrentScene().CreateLayer("World");

		GameObject* camera = GameObject::Instantiate(0, 0, 10);
		camera->AddComponent(new Camera(Projection::Orthographic));

		GameObject* object = GameObject::Instantiate(1280 / 2, 720 / 2, 0);
		object->AddComponent(new Mesh(ResourceManager::Library().CreateRectangle(200, 200, Color::White()), Material<Texture2D>(Color::White(), ResourceManager::Library().DefaultColorShader())));

		SceneManager::Instance().CurrentScene().GetLayer("World").SetActiveCamera(camera);

	}

	void Update() override
	{
		Graphics::CurrentContext()->SetTitle("RPG: " + std::to_string((int)Time::AvgFPS()));
		Application::Update();
	}

	void Render() override
	{
		Application::Render();
		
		if (SceneManager::Instance().HasScene())
		{
			for (GameObject* object : GameObject::GetAllWith<Transform, Mesh>())
			{
				RenderMesh(object->transform(), object->mesh(), object->GetLayer()->GetActiveCamera());
			}
		}

		UpdateDisplay();
	}

	void RenderMesh(const Transform& transform, const Mesh& mesh, GameObject* camera)
	{
		if (camera != nullptr)
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
	}

};

int main()
{
	Game g;
	g.Start();
	return 0;
}