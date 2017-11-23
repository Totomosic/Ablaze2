#pragma once
#include "Common.h"

#include "Framebuffer.h"
#include "GraphicsPipeline.h"
#include "Window.h"
#include "Resources\Resource.h"
#include "Resources\Textures\Fonts\Font.h"

namespace Ablaze
{

	class MaterialBase;
	class Mesh;

	enum class GraphicsAPI
	{
		OpenGL, DirectX, Vulkan
	};

	enum class DepthFunction : GLenum
	{
		Less = GL_LESS,
		Lequal = GL_LEQUAL,
		Equal = GL_EQUAL,
		Gequal = GL_GEQUAL,
		Greater = GL_GREATER
	};

	enum class BlendSrc : GLenum
	{
		SrcAlpha = GL_SRC_ALPHA,
		One = GL_ONE
	};

	enum class BlendDst : GLenum
	{
		OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
		One = GL_ONE
	};

	class AB_API Graphics
	{
	private:
		static Window* s_Context;
		static GraphicsPipeline* s_Pipeline; // May want multiple pipelines
		static GraphicsAPI s_API;

		static bool s_DepthEnabled;
		static bool s_BlendEnabled;
		static bool s_CullEnabled;
		static DepthFunction s_DepthFunction;
		static BlendSrc s_BlendSrcFunction;
		static BlendDst s_BlendDstFunction;

	public:
		Graphics() = delete;

		static bool IsInitialised();
		static Window* CurrentContext();
		static GraphicsAPI GetAPI();

		static bool IsDepthEnabled();
		static bool IsBlendEnabled();
		static bool IsCullEnabled();
		static DepthFunction GetDepthFunction();
		static BlendSrc GetBlendSrcFunction();
		static BlendDst GetBlendDstFunction();

		static void Initialise(Window* window, GraphicsAPI api = GraphicsAPI::OpenGL);
		static void Terminate();

		// Graphical window commands
		static void Clear();
		static void SetRenderTarget(const Framebuffer* const renderTarget);
		static void Present();

		// Drawing commands
		static void DrawString(const String& text, const Resource<Font>& font);

		// OpenGL state management
		static void ResetGLStates();
		static void SetDepth(bool enabled);
		static void SetBlend(bool enabled);
		static void SetCull(bool enabled);
		static void SetDepthFunction(DepthFunction depthFunction);
		static void SetBlendSrcFunction(BlendSrc blendFunction);
		static void SetBlendDstFunction(BlendDst blendFunction);
		static void EnableDepthTest();
		static void DisableDepthTest();
		static void EnableBlend();
		static void DisableBlend();
		static void EnableCull();
		static void DisableCull();

		friend class Window;

	private:
		static void ApplyGLStates();
		static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

	};

}