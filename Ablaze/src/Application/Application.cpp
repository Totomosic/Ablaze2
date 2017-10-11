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

	Window* Application::BuildWindow(int width, int height, const String& title, const Color& clearColor)
	{
		return new Window(width, height, title, clearColor);
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
			GLenum result = glGetError();
			if (result != GL_NO_ERROR)
			{
				AB_ERROR(String("GLerror: ") + (const char*)glewGetErrorString(result) + " (" + std::to_string(result) + ")");
			}
		}
	}

	void Application::ClearEvents()
	{
		Input::Update();
	}

}