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

	class AB_API Graphics
	{
	private:
		static Window* s_Context;
		static GraphicsPipeline* s_Pipeline; // May want multiple pipelines
		static GraphicsAPI s_API;

	public:
		Graphics() = delete;

		static bool IsInitialised();
		static Window* CurrentContext();
		static GraphicsAPI GetAPI();

		static void Initialise(Window* window, GraphicsAPI api = GraphicsAPI::OpenGL);
		static void Terminate();

		static void Clear();
		static void SetRenderTarget(const Framebuffer* const renderTarget);
		static void Present();

		static void ChangeGraphicsPipeline(GraphicsPipeline* pipeline);

	};

}