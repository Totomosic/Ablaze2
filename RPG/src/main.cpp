#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::VM;
using namespace Ablaze::Maths;

class Game : public Application
{
public:
	Framebuffer* fbo;
	GameObject* minimapCamera;

public:
	void Init() override
	{
		Window* window = new Window(1280, 720, "AblazeScape: ", Color::CornflowerBlue());
		Graphics::Initialise(window);
		Graphics::EnableCull();

		fbo = new Framebuffer(1280, 720, true);
		
		SceneManager::Instance().CreateScene();

		SceneManager::Instance().CurrentScene().CreateLayer("World");
		SceneManager::Instance().CurrentScene().SetCurrentLayer("World");

		GameObject* playerOrientation = GameObject::Load("playerOrientation.gameobject");
		GameObject* player = playerOrientation->Parent();		

		GameObject* camera = GameObject::Instantiate(nullptr, playerOrientation, 0, 0, 10);
		camera->AddComponent<Camera>();
		SceneManager::Instance().CurrentScene()["World"].SetActiveCamera(camera);

		GameObject* sun = GameObject::Instantiate(0, 15, 0);
		sun->AddComponent<Light>();

		minimapCamera = GameObject::Instantiate(nullptr, player, 0, 100, 0);
		minimapCamera->transform().Rotate(-Maths::PI / 2, Maths::Vec3(1, 0, 0));
		minimapCamera->AddComponent(new Camera(-10, 10, -10, 10));

		SceneManager::Instance().CurrentScene().CreateLayer("UI");
		SceneManager::Instance().CurrentScene().SetCurrentLayer("UI");

		GameObject* canvas = GameObject::Instantiate(0, 0, 10);
		canvas->AddComponent(new Camera(Projection::Orthographic));
		SceneManager::Instance().CurrentScene()["UI"].SetActiveCamera(canvas);

		GameObject* frame = GameObject::Instantiate(WindowWidth() - 275.0f / 2, WindowHeight() - 275.0f / 2, 0);
		frame->AddComponent(new Mesh(ResourceManager::Library().CreateRectangle(275, 275), Material<Texture2D>(Color(255, 255, 50, 100), ResourceManager::Library().DefaultColorShader())));
		GameObject* minimap = GameObject::Instantiate(nullptr, frame, 0, 0, 1);
		minimap->AddComponent(new Mesh(ResourceManager::Library().CreateCircle(275.0f / 2), Material<Texture2D>(Color::White(), ResourceManager::Library().DefaultTextureShader(), "Tex0", fbo->GetTexture(ColorBuffer::Color0))));
		minimap->transform().LocalScale() = Maths::Vec3(0.95f);

		GameObject* compass = GameObject::Instantiate(minimap, frame, -100, 100, 2);
		compass->transform().SetScale(0.2f);
		compass->mesh().SetMaterial(0, Material<Texture2D>(Color::White(), ResourceManager::Library().DefaultTextureShader(), "Tex0", "res/compass.jpg"));
		compass->SetTag("Compass");

		GameObject* ribbon = GameObject::Instantiate(WindowWidth() - 400, 12.5f, 0);
		ribbon->AddComponent(new Mesh(ResourceManager::Library().CreateRectangle(800, 25), Material<Texture2D>(Color::White(), ResourceManager::Library().DefaultColorShader())));

		GameObject* chatwindow = GameObject::Instantiate(200, 87.5, 0);
		chatwindow->AddComponent(new Mesh(ResourceManager::Library().CreateRectangle(400, 175), Material<Texture2D>(Color(50, 50, 255, 100), ResourceManager::Library().DefaultColorShader())));
		GameObject* chatbox = GameObject::Instantiate(chatwindow, chatwindow, 0, 0, 1);
		chatbox->transform().LocalScale() = Maths::Vec3(0.96f, 0.92f, 1);
		chatbox->mesh().Material(0).BaseColor() = Color(255, 255, 255, 100);

		JSONwriter writer("Saves/Scene.scene");
		writer.WriteObject(SceneManager::Instance().CurrentScene());

	}

	void Update() override
	{
		Graphics::CurrentContext()->SetTitle("AblazeScape: " + std::to_string((int)Time::AvgFPS()));

		GameObject& camera = *SceneManager::Instance().CurrentScene()["World"].GetActiveCamera();
		Transform& transform = SceneManager::Instance().CurrentScene()["World"].GetNamedGameObject("PlayerOrientation").transform();
		Transform& compass = SceneManager::Instance().CurrentScene()["UI"].GetNamedGameObject("Compass").transform();
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
			minimapCamera->transform().Rotate(Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(0, 1, 0), Space::World);
			compass.Rotate(-Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(0, 0, 1), Space::World);
		}
		if (Input::KeyDown(Keycode::Left))
		{
			transform.Rotate(-Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(0, 1, 0), Space::World);
			minimapCamera->transform().Rotate(-Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(0, 1, 0), Space::World);
			compass.Rotate(Maths::PI / 2 * Time::DeltaTime(), Maths::Vec3(0, 0, 1), Space::World);
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

		camera.transform().LocalPosition() += Maths::Vec3::Forward() * Input::RelMouseScroll().y;

		Application::Update();
	}

	void Render() override
	{
		fbo->Clear();
		for (GameObject* object : SceneManager::Instance().CurrentScene().GetLayer("World").GameObjects())
		{
			if (object->HasComponent<Transform>() && object->HasComponent<Mesh>())
			{
				RenderMesh(object->transform(), object->mesh(), minimapCamera);
			}
		}

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