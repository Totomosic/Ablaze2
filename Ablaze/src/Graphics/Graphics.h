#pragma once
#include "Common.h"

#include "Framebuffer.h"
#include "GraphicsPipeline.h"
#include "Window.h"

namespace Ablaze
{

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
		static DepthFunction GetDepthFunction();
		static BlendSrc GetBlendSrcFunction();
		static BlendDst GetBlendDstFunction();

		static void Initialise(Window* window, GraphicsAPI api = GraphicsAPI::OpenGL);
		static void Terminate();

		static void Clear();
		static void SetRenderTarget(const Framebuffer* const renderTarget);
		static void Present();

		static void ChangeGraphicsPipeline(GraphicsPipeline* pipeline);

		static void ResetGLStates();
		static void SetDepth(bool enabled);
		static void SetBlend(bool enabled);
		static void SetDepthFunction(DepthFunction depthFunction);
		static void SetBlendSrcFunction(BlendSrc blendFunction);
		static void SetBlendDstFunction(BlendDst blendFunction);
		static void EnableDepthTest();
		static void DisableDepthTest();
		static void EnableBlend();
		static void DisableBlend();

	private:
		static void ApplyGLStates();

	};

}