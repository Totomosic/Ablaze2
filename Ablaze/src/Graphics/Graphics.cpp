#include "Graphics.h"

namespace Ablaze
{

	Window* Graphics::s_Context = nullptr;
	GraphicsPipeline* Graphics::s_Pipeline = nullptr;
	GraphicsAPI Graphics::s_API = GraphicsAPI::OpenGL;

	bool Graphics::IsInitialised()
	{
		return s_Context != nullptr;
	}

	Window* Graphics::CurrentContext()
	{
		return s_Context;
	}

	GraphicsAPI Graphics::GetAPI()
	{
		return s_API;
	}

	void Graphics::Initialise(Window* window, GraphicsAPI api)
	{
		s_Context = window;
		s_API = api;
	}

	void Graphics::Terminate()
	{
		delete s_Context;
	}

	void Graphics::Clear()
	{
		s_Context->Clear();
	}

	void Graphics::SetRenderTarget(const Framebuffer* const renderTarget)
	{
		
	}

	void Graphics::Present()
	{
		s_Context->SwapBuffers();
	}

}