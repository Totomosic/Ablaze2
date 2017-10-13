#include "Graphics.h"

namespace Ablaze
{

	Window* Graphics::s_Context = nullptr;
	GraphicsPipeline* Graphics::s_Pipeline = nullptr;
	GraphicsAPI Graphics::s_API = GraphicsAPI::OpenGL;

	bool Graphics::s_DepthEnabled = false;
	bool Graphics::s_BlendEnabled = false;
	DepthFunction Graphics::s_DepthFunction = DepthFunction::Less;
	BlendSrc Graphics::s_BlendSrcFunction = BlendSrc::SrcAlpha;
	BlendDst Graphics::s_BlendDstFunction = BlendDst::OneMinusSrcAlpha;

	bool Graphics::IsInitialised()
	{
		return s_Context != nullptr;
	}

	Window* Graphics::CurrentContext()
	{
		if (!IsInitialised())
		{
			AB_FATAL("Window was never initialised, Call Graphics::Initialise(windowPtr)");
		}
		return s_Context;
	}

	GraphicsAPI Graphics::GetAPI()
	{
		return s_API;
	}

	bool Graphics::IsDepthEnabled()
	{
		return s_DepthEnabled;
	}

	bool Graphics::IsBlendEnabled()
	{
		return s_BlendEnabled;
	}

	DepthFunction Graphics::GetDepthFunction()
	{
		return s_DepthFunction;
	}

	BlendSrc Graphics::GetBlendSrcFunction()
	{
		return s_BlendSrcFunction;
	}

	BlendDst Graphics::GetBlendDstFunction()
	{
		return s_BlendDstFunction;
	}

	void Graphics::Initialise(Window* window, GraphicsAPI api)
	{
		s_Context = window;
		s_API = api;
		ResetGLStates();
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

	void Graphics::ResetGLStates()
	{
		s_DepthEnabled = false;
		s_BlendEnabled = false;
		s_DepthFunction = DepthFunction::Less;
		s_BlendSrcFunction = BlendSrc::SrcAlpha;
		s_BlendDstFunction = BlendDst::OneMinusSrcAlpha;
		ApplyGLStates();
	}

	void Graphics::SetDepth(bool enabled)
	{
		if (s_DepthEnabled != enabled)
		{
			s_DepthEnabled = enabled;
			if (s_DepthEnabled)
			{
				glEnable(GL_DEPTH_TEST);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
		}
	}

	void Graphics::SetBlend(bool enabled)
	{
		if (s_BlendEnabled != enabled)
		{
			s_BlendEnabled = enabled;
			if (s_BlendEnabled)
			{
				glEnable(GL_BLEND);
			}
			else
			{
				glDisable(GL_BLEND);
			}
		}
	}

	void Graphics::SetDepthFunction(DepthFunction depthFunction)
	{
		if (s_DepthFunction != depthFunction)
		{
			s_DepthFunction = depthFunction;
			glDepthFunc((GLenum)s_DepthFunction);
		}
	}

	void Graphics::SetBlendSrcFunction(BlendSrc function)
	{
		if (s_BlendSrcFunction != function)
		{
			s_BlendSrcFunction = function;
			glBlendFunc((GLenum)s_BlendSrcFunction, (GLenum)s_BlendDstFunction);
		}
	}

	void Graphics::SetBlendDstFunction(BlendDst function)
	{
		if (s_BlendDstFunction != function)
		{
			s_BlendDstFunction = function;
			glBlendFunc((GLenum)s_BlendSrcFunction, (GLenum)s_BlendDstFunction);
		}
	}

	void Graphics::EnableDepthTest()
	{
		SetDepth(true);
	}

	void Graphics::DisableDepthTest()
	{
		SetDepth(false);
	}

	void Graphics::EnableBlend()
	{
		SetBlend(true);
	}

	void Graphics::DisableBlend()
	{
		SetBlend(false);
	}

	void Graphics::ApplyGLStates()
	{
		if (s_DepthEnabled)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}

		if (s_BlendEnabled)
		{
			glEnable(GL_BLEND);
		}
		else
		{
			glDisable(GL_BLEND);
		}
		glDepthFunc((GLenum)s_DepthFunction);
		glBlendFunc((GLenum)s_BlendSrcFunction, (GLenum)s_BlendDstFunction);
	}

}