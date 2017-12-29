#pragma once
#include "Common.h"
#include "Framebuffer.h"
#include "System\Engine.h"

namespace Ablaze
{

	class AB_API Window : public Object
	{
	private:
		Framebuffer m_Framebuffer;
		String m_Title;
		GLFWwindow* m_WindowPtr;

	public:
		Window(int width, int height, const String& title, const Color& clearColor = Color::Black(), bool useDefaultHints = true);
		~Window();

		int Width() const;
		int Height() const;
		Maths::Vector2i Size() const;
		const String& Title() const;
		float Aspect() const;
		GLFWwindow* WindowHandle() const;
		const Framebuffer& GetFramebuffer() const;
		Framebuffer& GetFramebuffer();

		bool ShouldClose() const;
		void Close() const;
		void Clear(ClearBuffer clearBuffer = ClearBuffer::Color | ClearBuffer::Depth) const;
		void SwapBuffers() const;

		void EnableVSync() const;
		void DisableVSync() const;

		void SetWidth(int width);
		void SetHeight(int height);
		void SetTitle(const String& title);
		void SetClearColor(const Color& color);
		void SetIcon(const String& filename);

		String ToString() const override;

	private:
		void Create();
		void MakeCurrentContext();

	};

}