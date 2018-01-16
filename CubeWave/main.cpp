#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::Maths;
using namespace Ablaze::VM;
using namespace Ablaze::Networking;

#include "src\Wave.h"

namespace CubeWave
{

	class Sketch : public Application
	{
	public:
		Scene* scene;

	public:
		void Init() override
		{
			Window* window = new Window(1280, 720, "Sketch", Color::CornflowerBlue());
			Graphics::Initialise(window);

			SocketAddress addr("localhost", 8000);
			UDPsocket* server = CreateUDPSocket();
			UDPsocket* client = CreateUDPSocket();

			server->Bind(addr);
			Vector3f send(5, 0, -5);
			client->SendTo(&send, sizeof(Vector3f), addr);
			Vector3f recv;
			server->ReceiveFrom(&recv, sizeof(Vector3f), nullptr);
			AB_INFO(recv);

			delete server;
			delete client;

			GraphicsPipeline g;
			g.Renderer = new ForwardRenderer;
			g.Schedule = new RenderSchedule;
			g.Schedule->AddRenderPass(new RenderPass("Default"));
			Graphics::AddGraphicsPipeline(g);
		}

		void Tick() override
		{
			
		}

		void Update() override
		{
			Application::Update();
		}

		void Render() override
		{
			Graphics::Clear();
			Graphics::RenderScene();
			Graphics::Present();
		}

	};

}

int main()
{
	CubeWave::Sketch sketch;
	sketch.Start();
	return 0;
}