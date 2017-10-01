#include "Ablaze.h"

using namespace Ablaze;

class Game : public Application
{
private:
	Window* m_Window;
	VertexArray* vao;
	Texture2D* texture;

public:
	void Init() override
	{
		m_Window = BuildWindow(1280, 720, "Ablaze: 60", Color::White());
		Graphics::Initialise(m_Window);

		Resource<Shader> s = ResourceManager::Library().LoadShader("base_v.glsl", "base_f.glsl");
		s.Increment();
		s->Bind();

		Resource<Texture2D> tex = ResourceManager::Library().LoadTexture2D("image.png", MipmapMode::Enabled);
		tex.Increment();
		texture = *tex;

		vao = ResourceManager::Library().CreateRectangle(2, 2).Get()->GetVertexArray();

		File f = FileSystem::CreateNew("test.txt");
		FileSystem::WriteText(f, "Hi");

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
		
		texture->Bind();

		vao->Bind();
		glDrawElements((GLenum)vao->GetRenderMode(), vao->RenderCount(), GL_UNSIGNED_INT, nullptr);

		UpdateDisplay();
	}

};

int main()
{
	Game g;
	g.Start();
	return 0;
}