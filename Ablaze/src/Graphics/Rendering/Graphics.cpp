#include "Graphics.h"
#include "Resources\ResourceManager.h"
#include "Resources\Meshes\__Meshes__.h"

#include "Renderers\Methods\__Methods__.h"

namespace Ablaze
{

	Window* Graphics::s_Context = nullptr;
	GraphicsAPI Graphics::s_API = GraphicsAPI::OpenGL;

	bool Graphics::s_DepthEnabled = false;
	bool Graphics::s_BlendEnabled = false;
	bool Graphics::s_CullEnabled = false;
	DepthFunction Graphics::s_DepthFunction = DepthFunction::Less;
	BlendSrc Graphics::s_BlendSrcFunction = BlendSrc::SrcAlpha;
	BlendDst Graphics::s_BlendDstFunction = BlendDst::OneMinusSrcAlpha;

	std::vector<GraphicsPipeline> Graphics::s_Pipelines = std::vector<GraphicsPipeline>();
	GraphicsPipeline* Graphics::s_CurrentPipeline = nullptr;

	bool Graphics::IsInitialised()
	{
		return s_Context != nullptr;
	}

	Window& Graphics::CurrentContext()
	{
		if (!IsInitialised())
		{
			AB_FATAL("Window was never initialised, Call Graphics::Initialise(windowPtr)");
		}
		return *s_Context;
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

	bool Graphics::IsCullEnabled()
	{
		return s_CullEnabled;
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

		ResourceManager::Initialise();
	}

	void Graphics::Terminate()
	{
		delete s_Context;
	}

	void Graphics::Clear()
	{
		s_Context->Clear();
	}

	void Graphics::Present()
	{
		s_Context->SwapBuffers();
	}

	void Graphics::AddGraphicsPipeline(const GraphicsPipeline& pipeline)
	{
		int index = s_Pipelines.size();
		s_Pipelines.push_back(pipeline);
		if (s_CurrentPipeline == nullptr)
		{
			s_CurrentPipeline = &s_Pipelines[index];
		}
	}

	void Graphics::EnableGraphicsPipeline(int index)
	{
		s_CurrentPipeline = &s_Pipelines[index];
	}

	void Graphics::RenderScene()
	{
		if (s_CurrentPipeline != nullptr)
		{
			s_CurrentPipeline->Schedule->Execute(*s_CurrentPipeline->Renderer);
		}
		else
		{
			AB_WARN("Attempted to render scene without active GraphicsPipeline");
		}
	}

	void Graphics::DrawString(float x, float y, const String& text, Font* font, const Color& color)
	{
		GameObject* obj = GameObject::Instantiate("Object", x, y, 0);
		obj->AddComponent(new MeshRenderer(new Mesh(font->CreateModel(text), new Material(color, ResourceManager::DefaultFontShader(), "Tex0", font))));
		GameObject* camera = GameObject::Instantiate("Camera", 0, 0, 10);
		camera->AddComponent(new Camera(Projection::Orthographic));

		ForwardRenderMethod method;
		method.Begin();
		method.Render(obj, camera);
		method.End();

		obj->Destroy();
		camera->Destroy();
	}

	void Graphics::DrawRectangle(float x, float y, float w, float h, Material* material)
	{
		GameObject* obj = GameObject::Instantiate("Object", x, y, 0);
		obj->transform().LocalScale() = Maths::Vector3f(w, h, 1);
		obj->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), material)));
		GameObject* camera = GameObject::Instantiate("Camera", 0, 0, 10);
		camera->AddComponent(new Camera(Projection::Orthographic));

		ForwardRenderMethod method;
		method.Begin();
		method.Render(obj, camera);
		method.End();

		obj->Destroy();
		camera->Destroy();
	}

	void Graphics::DrawRectangle(float x, float y, float w, float h, const Color& color)
	{
		DrawRectangle(x, y, w, h, new Material(color, ResourceManager::DefaultColorShader()));
	}

	void Graphics::DrawImage(float x, float y, float w, float h, Texture2D* image)
	{
		DrawRectangle(x, y, w, h, new Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", image));
	}

	void Graphics::ResetGLStates()
	{
		s_DepthEnabled = false;
		s_BlendEnabled = false;
		s_CullEnabled = false;
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
				GL_CALL(glEnable(GL_DEPTH_TEST));
			}
			else
			{
				GL_CALL(glDisable(GL_DEPTH_TEST));
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
				GL_CALL(glEnable(GL_BLEND));
			}
			else
			{
				GL_CALL(glDisable(GL_BLEND));
			}
		}
	}

	void Graphics::SetCull(bool enabled)
	{
		if (s_CullEnabled != enabled)
		{
			s_CullEnabled = enabled;
			if (s_CullEnabled)
			{
				GL_CALL(glEnable(GL_CULL_FACE));
			}
			else
			{
				GL_CALL(glDisable(GL_CULL_FACE));
			}
		}
	}

	void Graphics::SetDepthFunction(DepthFunction depthFunction)
	{
		if (s_DepthFunction != depthFunction)
		{
			s_DepthFunction = depthFunction;
			GL_CALL(glDepthFunc((GLenum)s_DepthFunction));
		}
	}

	void Graphics::SetBlendSrcFunction(BlendSrc function)
	{
		if (s_BlendSrcFunction != function)
		{
			s_BlendSrcFunction = function;
			GL_CALL(glBlendFunc((GLenum)s_BlendSrcFunction, (GLenum)s_BlendDstFunction));
		}
	}

	void Graphics::SetBlendDstFunction(BlendDst function)
	{
		if (s_BlendDstFunction != function)
		{
			s_BlendDstFunction = function;
			GL_CALL(glBlendFunc((GLenum)s_BlendSrcFunction, (GLenum)s_BlendDstFunction));
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

	void Graphics::EnableCull()
	{
		SetCull(true);
	}

	void Graphics::DisableCull()
	{
		SetCull(false);
	}

	void Graphics::ApplyGLStates()
	{
		if (s_DepthEnabled)
		{
			GL_CALL(glEnable(GL_DEPTH_TEST));
		}
		else
		{
			GL_CALL(glDisable(GL_DEPTH_TEST));
		}

		if (s_BlendEnabled)
		{
			GL_CALL(glEnable(GL_BLEND));
		}
		else
		{
			GL_CALL(glDisable(GL_BLEND));
		}

		if (s_CullEnabled)
		{
			GL_CALL(glEnable(GL_CULL_FACE));
		}
		else
		{
			GL_CALL(glDisable(GL_CULL_FACE));
		}
		GL_CALL(glDepthFunc((GLenum)s_DepthFunction));
		GL_CALL(glBlendFunc((GLenum)s_BlendSrcFunction, (GLenum)s_BlendDstFunction));
	}

	void Graphics::FramebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		CurrentContext().SetWidth(width);
		CurrentContext().SetHeight(height);
	}

}