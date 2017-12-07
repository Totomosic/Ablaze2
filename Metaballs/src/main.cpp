#include "Ablaze.h"
#include "Radius.h"

using namespace Ablaze;
using namespace Ablaze::Maths;

class Game : public Application
{
public:
	Window* window;

public:
	void Init()
	{
		window = new Window(1280, 720, "Isosurface: 60");
		Graphics::Initialise(window);

		Scene& scene = SceneManager::Instance().CreateScene();
		scene.CreateLayer("Canvas");

		GameObject* camera = GameObject::Instantiate("Camera", 0, 0, 10);
		camera->AddComponent(new Camera(Projection::Orthographic));

		GameObject* canvas = GameObject::Instantiate("Canvas", WindowWidth() / 2, WindowHeight() / 2, 0);
		canvas->AddComponent(new Mesh(ResourceManager::Instance().Square(), std::make_shared<Material<>>(Color::White(), ResourceManager::Instance().LoadShader("res/Metaballs.shader"))));
		canvas->transform().LocalScale() = Maths::Vector3f(WindowWidth(), WindowHeight(), 1);

		scene.CurrentLayer().SetActiveCamera(camera);

		GraphicsPipeline g;
		g.Renderer = new ForwardRenderer;
		g.Schedule = new RenderSchedule;
		g.Schedule->AddRenderPass(new RenderPass("Default"));
		Graphics::AddGraphicsPipeline(g);

	}

	void AddMetaball()
	{
		GameObject* ball = GameObject::Instantiate("Metaball", Input::MousePosition().x, Input::MousePosition().y, 0);
		ball->AddComponent<RigidBody>();
		Color c = Color::Random();
		//Color c = Color::White();
		ball->AddComponent(new Radius(Random::NextFloat(75, 200), c));
		//ball->AddComponent(new Mesh(ResourceManager::Instance().Circle(), std::make_shared<Material<>>(Color::Magenta(), ResourceManager::Instance().DefaultColorShader())));
		//ball->transform().LocalScale() = Maths::Vector3f(ball->GetComponent<Radius>().radius);
		RigidBody& rb = ball->GetComponent<RigidBody>();
		rb.Velocity() = Maths::Vector3f(Random::NextFloat(-250, 250), Random::NextFloat(-250, 250), 0);
	}

	void Reset()
	{
		for (GameObject* metaball : SceneManager::Instance().CurrentScene().CurrentLayer().GetNamedGameObjects("Metaball"))
		{
			metaball->Destroy();
		}
	}

	void Update()
	{
		window->SetTitle("Isosurface: " + std::to_string((int)Time::AvgFPS()));

		if (Input::MouseButtonReleased(MouseButton::Left))
		{
			AddMetaball();
		}
		if (Input::KeyPressed(Keycode::R))
		{
			Reset();
		}

		GameObject& canvas = SceneManager::Instance().CurrentScene().CurrentLayer().GetNamedGameObject("Canvas");
		Material<Texture2D>* material = (Material<Texture2D>*)canvas.mesh().Material(0).get();

		std::vector<GameObject*> metaballs = SceneManager::Instance().CurrentScene().CurrentLayer().GetNamedGameObjects("Metaball");
		int index = 0;
		for (GameObject* ball : metaballs)
		{
			Transform& t = ball->transform();
			RigidBody& r = ball->GetComponent<RigidBody>();
			if (t.Position().x < 0)
			{
				r.Velocity().x *= -1;
				r.Velocity().y += Random::NextFloat(-20, 20);
				t.LocalPosition().x = 1;
			}
			if (t.Position().x > WindowWidth())
			{
				r.Velocity().x *= -1;
				r.Velocity().y += Random::NextFloat(-20, 20);
				t.LocalPosition().x = WindowWidth() - 1;
			}
			if (t.Position().y < 0)
			{
				r.Velocity().y *= -1;
				r.Velocity().x += Random::NextFloat(-20, 20);
				t.LocalPosition().y = 1;
			}
			if (t.Position().y > WindowHeight())
			{
				r.Velocity().y *= -1;
				r.Velocity().x += Random::NextFloat(-20, 20);
				t.LocalPosition().y = WindowHeight() - 1;
			}
			material->Uniforms().AddUniform("Metaballs[" + std::to_string(index) + "].Position", ball->transform().Position().xy(), UniformUploadMode::Once);
			material->Uniforms().AddUniform<float>("Metaballs[" + std::to_string(index) + "].Radius", ball->GetComponent<Radius>().radius, UniformUploadMode::Once);
			material->Uniforms().AddUniform("Metaballs[" + std::to_string(index) + "].Color", ball->GetComponent<Radius>().color, UniformUploadMode::Once);
			index++;
		}
		material->Uniforms().AddUniform("ballCount", (int)metaballs.size(), UniformUploadMode::Once);

		Application::Update();
	}

	void Render()
	{
		Application::Render();
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