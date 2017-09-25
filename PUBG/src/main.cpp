#include "Ablaze.h"

using namespace Ablaze;

class Game : public Application
{
private:
	VertexArray* vao;

public:
	void Init() override
	{
		BuildWindow(1280, 720, "Ablaze: 60", Color::White());

		Shader* s = ResourceManager::Get()->CreateShader("base_v.glsl", "base_f.glsl");
		s->Bind();

		Texture2D* tex = ResourceManager::Get()->CreateTexture2D("image.png");
		tex->Bind();

		float* data = new float[2 * 2 * 4]{ -0.5f, 0.5f, 0.0, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f };
		uint* indices = new uint[6]{ 0, 1, 2, 0, 2, 3 };

		BufferLayout layout;
		layout.AddAttribute(Attribute::Position, 2);
		layout.AddAttribute(Attribute::TexCoord, 2);

		VertexBuffer* vbo = new VertexBuffer(data, 2 * 2 * 4 * sizeof(float), layout);
		IndexBuffer* indexBuffer = new IndexBuffer(indices, 6 * sizeof(uint));

		vao = new VertexArray(indexBuffer);
		vao->AddVertexBuffer(vbo);

		File f = FileSystem::CreateNew("test.txt");
		FileSystem::WriteText(f, "Hi");

		delete[] data;
		delete[] indices;
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