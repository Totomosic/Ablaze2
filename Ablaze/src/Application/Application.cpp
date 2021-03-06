#include "Application.h"
#include "Time.h"
#include "Graphics\Rendering\Graphics.h"
#include "Scene\Systems\Systems.h"

#include "Scene\Components\__Components__.h"

#include "System\Networking\NetworkIncludes.h"

namespace Ablaze
{

	Application::Application() : Object()
	{

	}

	Application::~Application()
	{
		Engine::Shutdown();
	}

	void Application::Start()
	{
		int glfwResult = glfwInit();
		if (glfwResult != GLFW_TRUE)
		{
			AB_FATAL("Failed to initialise GLFW");
		}
		SetupConsole(AB_LOG_LEVEL_INFO);

		// Initialise socket libraries
		WSADATA data;
		if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
		{
			AB_FATAL("Failed to initalise WinSock2");
		}

		double time = Time::CurrentTime();
		Init();
		AB_WARN("Init took: " + std::to_string(Time::CurrentTime() - time) + " seconds");
		Time::Reset();
		Time::CreateNewTimer(1.0, METHOD_0(Application::Tick));

		Run();
	}

	int Application::WindowWidth()
	{
		return Graphics::CurrentContext().Width();
	}

	int Application::WindowHeight()
	{
		return Graphics::CurrentContext().Height();
	}

	String Application::ToString() const
	{
		return "Application";
	}

	void Application::UpdateDisplay()
	{
		Graphics::Present();
	}

	void Application::Quit()
	{
		Graphics::CurrentContext().Close();
	}

	void Application::Init()
	{
	
	}

	void Application::Tick()
	{
		
	}

	void Application::Update()
	{
		Systems::Run();
	}

	void Application::Render()
	{
		
	}

	void Application::Run()
	{
		while (!Graphics::CurrentContext().ShouldClose())
		{
			Time::Update();
			Input::Start();
			Update();

			if (SceneManager::Instance().HasScene())
			{
				for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers())
				{
					layer->Clean();
				}
			}

			if (Graphics::IsInitialised())
			{
				Render();
			}
			Debugger::Update();
			Input::End();
		}
	}

}