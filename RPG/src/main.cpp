#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::VM;
using namespace Ablaze::Maths;

class Game : public Application
{
public:
	Framebuffer* renderTarget;

public:
	void Init() override
	{
		Window* window = new Window(1280, 720, "AblazeScape: ", Color::CornflowerBlue(), false);
		Graphics::Initialise(window);
		Graphics::EnableCull();

		renderTarget = new Framebuffer(WindowWidth(), WindowHeight(), true);
		renderTarget->SetClearColor(Color::CornflowerBlue());

		/*SceneManager::Instance().CreateScene();
		SceneManager::Instance().CurrentScene().CreateLayer("World");
		SceneManager::Instance().CurrentScene().SetCurrentLayer(0);

		GameObject* player = GameObject::Instantiate("Player", 0, 0, 0);
		player->AddComponent(new Mesh(ResourceManager::Instance().CreateCuboid(1, 1, 1), Material<>(Color::White(), ResourceManager::Instance().LightingTextureShader(), "Tex0", "res/canyonTerrain.png")));
		GameObject* playerOrientation = GameObject::Instantiate("PlayerOrientation", nullptr, player, 0, 0, 0);

		GameObject* terrain = GameObject::Instantiate("Terrain", 0, -0.5f, 0);
		terrain->AddComponent(new Mesh(ResourceManager::Instance().CreatePlane(15, 15), Material<>(Color::Green(), ResourceManager::Instance().LightingColorShader())));

		GameObject* camera = GameObject::Instantiate("Camera", nullptr, playerOrientation, 0, 0, 10);
		camera->AddComponent<Camera>();

		GameObject* sun = GameObject::Instantiate("Sun", 0, 100, 0);
		sun->AddComponent<Light>();

		SceneManager::Instance().CurrentScene().CurrentLayer().SetActiveCamera(camera);

		SceneManager::Instance().CurrentScene().CreateLayer("UI");
		SceneManager::Instance().CurrentScene().SetCurrentLayer("UI");

		GameObject* canvas = GameObject::Instantiate("Canvas", 0, 0, 100);
		canvas->AddComponent(new Camera(Projection::Orthographic));

		GameObject* rect = GameObject::Instantiate("Crosshair", WindowWidth() / 2, WindowHeight() / 2, 0);
		rect->AddComponent(new Mesh(ResourceManager::Instance().CreateRectangle(15, 15), Material<>(Color::Red(), ResourceManager::Instance().DefaultColorShader())));

		SceneManager::Instance().CurrentScene().CurrentLayer().SetActiveCamera(canvas);*/

		// Render Setup
		GraphicsPipeline g;
		g.Renderer = new ForwardRenderer;
		g.Schedule = new RenderSchedule;
		g.Schedule->AddRenderPass(new RenderPass("Default", renderTarget));
		Graphics::AddGraphicsPipeline(g);

	}

	void Update() override
	{
		/*Graphics::CurrentContext()->SetTitle("AblazeScape: " + std::to_string((int)Time::AvgFPS()));

		GameObject& camera = *SceneManager::Instance().CurrentScene()["World"].GetActiveCamera();
		Transform& transform = SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("PlayerOrientation").transform();

		if (Input::KeyDown(Keycode::Down))
		{
			transform.Rotate(Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(1, 0, 0), Space::Local);
		}
		if (Input::KeyDown(Keycode::Up))
		{
			transform.Rotate(-Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(1, 0, 0), Space::Local);
		}
		if (Input::KeyDown(Keycode::Right))
		{
			transform.Rotate(Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(0, 1, 0), Space::World);
		}
		if (Input::KeyDown(Keycode::Left))
		{
			transform.Rotate(-Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(0, 1, 0), Space::World);
		}

		Transform& player = SceneManager::Instance().CurrentScene().GetLayer("World").GetNamedGameObject("Player").transform();
		float speed = 3;
		if (Input::KeyDown(Keycode::W))
		{
			player.LocalPosition() += player.Forward() * speed * Time::DeltaTime();
		}
		if (Input::KeyDown(Keycode::S))
		{
			player.LocalPosition() -= player.Forward() * speed * Time::DeltaTime();
		}

		camera.transform().LocalPosition() += Maths::Vec3::Forward() * Input::RelMouseScroll().y;*/

		Application::Update();
	}

	void Render() override
	{
		Application::Render();

		Graphics::Clear();
		Graphics::RenderScene();
		Graphics::DrawRectangle(300, 300, 100, 50, Color::Blue());
		renderTarget->CopyToScreen(ClearBuffer::Color, Filter::Nearest);
		Graphics::Present();

		/*if (SceneManager::Instance().HasScene())
		{
			for (GameObject* object : GameObject::GetAllWith<Transform, Mesh>())
			{
				RenderMesh(object->transform(), object->mesh(), object->GetLayer()->GetActiveCamera());
			}
		}*/
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