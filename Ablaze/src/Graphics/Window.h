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

		String ToString() const override;

	private:
		void Create();
		void MakeCurrentContext();

	};

}