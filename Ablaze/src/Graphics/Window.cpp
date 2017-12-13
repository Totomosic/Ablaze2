#include "Window.h"
#include "Application\Input\Input.h"
#include "Rendering\Graphics.h"

namespace Ablaze
{

	Window::Window(int width, int height, const String& title, const Color& clearColor, bool useDefaultHints) : Object(),
		m_Framebuffer(*Framebuffer::WindowFramebuffer(width, height)), m_Title(title)
	{
		if (useDefaultHints)
		{
			glfwWindowHint(GLFW_SAMPLES, 4);
		}
		m_Framebuffer.SetClearColor(clearColor);
		Create();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_WindowPtr);
	}

	int Window::Width() const
	{
		return m_Framebuffer.GetWidth();
	}

	int Window::Height() const
	{
		return m_Framebuffer.GetHeight();
	}

	Maths::Vector2i Window::Size() const
	{
		return m_Framebuffer.GetViewport().Size();
	}

	float Window::Aspect() const
	{
		return m_Framebuffer.GetAspect();
	}

	const String& Window::Title() const
	{
		return m_Title;
	}

	GLFWwindow* Window::WindowHandle() const
	{
		return m_WindowPtr;
	}

	const Framebuffer& Window::GetFramebuffer() const
	{
		return m_Framebuffer;
	}

	Framebuffer& Window::GetFramebuffer()
	{
		return m_Framebuffer;
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
		glfwSetWindowSize(m_WindowPtr, Width(), Height());
	}

	void Window::SetHeight(int height)
	{
		m_Framebuffer.SetHeight(height);
		glfwSetWindowSize(m_WindowPtr, Width(), Height());
	}

	void Window::SetTitle(const String& title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_WindowPtr, m_Title.c_str());
	}

	void Window::SetClearColor(const Color& color)
	{
		m_Framebuffer.SetClearColor(color);
	}

	void Window::SetIcon(const String& filename)
	{
		uint width;
		uint height;
		int comp;
		byte* pixelData = LoadImageFile(filename, &width, &height, &comp, false);
		GLFWimage image;
		image.width = width;
		image.height = height;
		image.pixels = pixelData;
		glfwSetWindowIcon(m_WindowPtr, 1, &image);
		FreeImageData(pixelData);
	}

	String Window::ToString() const
	{
		return m_Title;
	}

	void Window::Create()
	{
		m_WindowPtr = glfwCreateWindow(Width(), Height(), m_Title.c_str(), nullptr, nullptr);
		MakeCurrentContext();
		Engine::Initialise();
	}

	void Window::MakeCurrentContext()
	{
		glfwMakeContextCurrent(m_WindowPtr);

		glfwSetKeyCallback(WindowHandle(), Input::KeyPressedCallback);
		glfwSetCursorPosCallback(WindowHandle(), Input::MousePositionCallback);
		glfwSetScrollCallback(WindowHandle(), Input::MouseScrollCallback);
		glfwSetMouseButtonCallback(WindowHandle(), Input::MousePressedCallback);
		glfwSetCharCallback(WindowHandle(), Input::CharPressedCallback);
		glfwSetFramebufferSizeCallback(WindowHandle(), Graphics::FramebufferResizeCallback);
	}

}