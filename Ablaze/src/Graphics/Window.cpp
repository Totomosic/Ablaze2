#include "Window.h"
#include "Application\Input\Input.h"

namespace Ablaze
{

	const Window* Window::s_CurrentContext = nullptr;
	
	Window::Window(int width, int height, const String& title, const Color& clearColor) : Object(),
		m_Framebuffer(*Framebuffer::WindowFramebuffer(width, height)), m_Title(title)
	{
		m_Framebuffer.SetClearColor(clearColor);
		Create();
	}

	Window::~Window()
	{
	
	}

	int Window::GetWidth() const
	{
		return m_Framebuffer.GetWidth();
	}

	int Window::GetHeight() const
	{
		return m_Framebuffer.GetHeight();
	}

	float Window::GetAspect() const
	{
		return m_Framebuffer.GetAspect();
	}

	const String& Window::GetTitle() const
	{
		return m_Title;
	}

	GLFWwindow* Window::WindowHandle() const
	{
		return m_WindowPtr;
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_WindowPtr);
	}

	void Window::Close() const
	{
		glfwSetWindowShouldClose(m_WindowPtr, true);
	}

	void Window::Clear(ClearBuffer buffer) const
	{
		m_Framebuffer.Clear(buffer);
	}

	void Window::Update() const
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(m_WindowPtr);
	}

	void Window::EnableVSync() const
	{
		glfwSwapInterval(1);
	}

	void Window::DisableVSync() const
	{
		glfwSwapInterval(0);
	}

	void Window::SetWidth(int width)
	{
		m_Framebuffer.SetWidth(width);
		glfwSetWindowSize(m_WindowPtr, GetWidth(), GetHeight());
	}

	void Window::SetHeight(int height)
	{
		m_Framebuffer.SetHeight(height);
		glfwSetWindowSize(m_WindowPtr, GetWidth(), GetHeight());
	}

	void Window::SetTitle(const String& title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_WindowPtr, m_Title.c_str());
	}

	String Window::ToString() const
	{
		return m_Title;
	}

	const Window* Window::Current()
	{
		return s_CurrentContext;
	}

	void Window::Create()
	{
		int glfwResult = glfwInit();
		if (glfwResult != GLFW_TRUE)
		{
			AB_FATAL("Failed to initialise GLFW");
		}
		m_WindowPtr = glfwCreateWindow(GetWidth(), GetHeight(), m_Title.c_str(), nullptr, nullptr);
		MakeCurrentContext();
		Engine::Initialise();
	}

	void Window::MakeCurrentContext()
	{
		glfwMakeContextCurrent(m_WindowPtr);
		s_CurrentContext = this;

		glfwSetKeyCallback(WindowHandle(), Input::KeyPressedCallback);
		glfwSetCursorPosCallback(WindowHandle(), Input::MousePositionCallback);
		glfwSetScrollCallback(WindowHandle(), Input::MouseScrollCallback);
		glfwSetMouseButtonCallback(WindowHandle(), Input::MousePressedCallback);
	}

}