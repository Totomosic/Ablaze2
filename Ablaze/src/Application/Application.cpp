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
		Graphics::CurrentContext()->SwapBuffers();
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
			ClearEvents();
		}
	}

	void Application::ClearEvents()
	{
		Input::Update();
	}

}