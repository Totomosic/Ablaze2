#include "Application.h"
#include "Time.h"
#include "Graphics\Graphics.h"

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
		Init();
		Time::Reset();
		Time::CreateNewTimer(1.0, std::bind(&Application::Tick, this));
		Run();
	}

	int Application::WindowWidth()
	{
		return Graphics::CurrentContext()->GetWidth();
	}

	int Application::WindowHeight()
	{
		return Graphics::CurrentContext()->GetHeight();
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
		Graphics::CurrentContext()->Close();
	}

	void Application::Init()
	{
	
	}

	void Application::Tick()
	{
		
	}

	void Application::Update()
	{
	
	}

	void Application::Render()
	{
		Graphics::CurrentContext()->Update();
		Graphics::CurrentContext()->Clear();
	}

	void Application::Run()
	{
		while (!Graphics::CurrentContext()->ShouldClose())
		{
			Time::Update();
			Update();
			if (Graphics::IsInitialised())
			{
				Render();
			}
			Debugger::Update();
			ClearEvents();
		}
	}

	void Application::ClearEvents()
	{
		Input::Update();
	}

}