#pragma once
#include "Common.h"
#include "GraphicsEnums.h"

#include "Graphics\Framebuffer.h"
#include "Graphics\Window.h"
#include "Resources\Textures\Fonts\Font.h"

#include "GraphicsPipeline.h"

namespace Ablaze
{

	class MaterialBase;
	class Mesh;

	class AB_API Graphics
	{
	private:
		static Window* s_Context;
		static GraphicsAPI s_API;

		static bool s_DepthEnabled;
		static bool s_BlendEnabled;
		static bool s_CullEnabled;
		static DepthFunction s_DepthFunction;
		static BlendSrc s_BlendSrcFunction;
		static BlendDst s_BlendDstFunction;

	private:
		static std::vector<GraphicsPipeline> s_Pipelines;
		static GraphicsPipeline* s_CurrentPipeline;

	public:
		Graphics() = delete;

		static bool IsInitialised();
		static Window& CurrentContext();
		static GraphicsAPI GetAPI();

		static bool IsDepthEnabled();
		static bool IsBlendEnabled();
		static bool IsCullEnabled();
		static DepthFunction GetDepthFunction();
		static BlendSrc GetBlendSrcFunction();
		static BlendDst GetBlendDstFunction();

		static void Initialise(Window* window, GraphicsAPI api = GraphicsAPI::OpenGL);
		static void Terminate();

		// Clear window
		static void Clear();
		// Update window display
		static void Present();

		static void AddGraphicsPipeline(const GraphicsPipeline& pipeline);
		static void EnableGraphicsPipeline(int index);
		static void RenderScene();

		static void DrawString(float x, float y, const String& text, Font* font, const Color& color = Color::White());
		static void DrawRectangle(float x, float y, float w, float h, Material<Texture2D>* material);
		static void DrawRectangle(float x, float y, float w, float h, const Color& color);
		static void DrawImage(float x, float y, float w, float h, Texture2D* image);

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