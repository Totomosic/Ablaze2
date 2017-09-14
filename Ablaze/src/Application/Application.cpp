#include "Application.h"
#include "Time.h"

namespace Ablaze
{

	Application::Application() : Object(),
		m_Window(nullptr)
	{

	}

	Application::~Application()
	{
		Engine::Shutdown();
	}

	void Application::Start()
	{
		Init();
		if (m_Window == nullptr)
		{
			AB_FATAL("No window was created during the Init method.");
			AB_FATAL("Use BuildWindow() to create window");
			return;
		}
		Time::Reset();
		Run();
	}

	Window* Application::WindowHandle()
	{
		return m_Window;
	}

	int Application::WindowWidth()
	{
		return m_Window->GetWidth();
	}

	int Application::WindowHeight()
	{
		return m_Window->GetHeight();
	}

	Window* Application::BuildWindow(int width, int height, const String& title, const Color& clearColor)
	{
		m_Window = new Window(width, height, title, clearColor);
		return m_Window;
	}

	String Application::ToString() const
	{
		return "Application";
	}

	void Application::UpdateDisplay()
	{
		m_Window->SwapBuffers();
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
		m_Window->Update();
		m_Window->Clear();
	}

	void Application::Run()
	{
		while (!m_Window->ShouldClose())
		{
			Time::Update();
			Update();
			Render();
			ClearEvents();
		}
	}

	void Application::ClearEvents()
	{
		Input::Update();
	}

}