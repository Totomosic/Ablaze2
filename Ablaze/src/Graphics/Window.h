#pragma once
#include "Common.h"
#include "Framebuffer.h"
#include "System\Engine.h"

namespace Ablaze
{

	class AB_API Window : public Object
	{
	private:
		static const Window* s_CurrentContext;

	private:
		Framebuffer m_Framebuffer;
		String m_Title;
		GLFWwindow* m_WindowPtr;

	public:
		Window(int width, int height, const String& title, const Color& clearColor = Color::Black());
		~Window();

		int GetWidth() const;
		int GetHeight() const;
		const String& GetTitle() const;
		float GetAspect() const;
		GLFWwindow* WindowHandle() const;

		bool ShouldClose() const;
		void Close() const;
		void Clear(ClearBuffer clearBuffer = ClearBuffer::Color | ClearBuffer::Depth) const;
		void Update() const;
		void SwapBuffers() const;

		void EnableVSync() const;
		void DisableVSync() const;

		void SetWidth(int width);
		void SetHeight(int height);
		void SetTitle(const String& title);
		void SetClearColor(const Color& color);
		void SetIcon(const String& filename);

		String ToString() const override;

	public:
		static const Window* Current();

	private:
		void Create();
		void MakeCurrentContext();

	};

}