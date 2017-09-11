#include "Viewport.h"

namespace Ablaze
{

	Viewport::Viewport(int x, int y, int width, int height) : Object(),
		m_XOff(x), m_YOff(y), m_Width(width), m_Height(height)
	{
	
	}

	Viewport::Viewport(int width, int height) : Viewport(0, 0, width, height)
	{
		
	}

	int Viewport::GetX() const
	{
		return m_XOff;
	}

	int Viewport::GetY() const
	{
		return m_YOff;
	}

	int Viewport::GetWidth() const
	{
		return m_Width;
	}

	int Viewport::GetHeight() const
	{
		return m_Height;
	}

	float Viewport::GetAspect() const
	{
		return (float)GetWidth() / GetHeight();
	}

	void Viewport::SetX(int x)
	{
		m_XOff = x;
	}

	void Viewport::SetY(int y)
	{
		m_YOff = y;
	}

	void Viewport::SetWidth(int width)
	{
		m_Width = width;
	}

	void Viewport::SetHeight(int height)
	{
		m_Height = height;
	}

	void Viewport::Bind() const
	{
		glViewport(GetX(), GetY(), GetWidth(), GetHeight());
	}

	void Viewport::Unbind() const
	{
		// Does nothing
	}

	String Viewport::ToString() const
	{
		return "Viewport(" + std::to_string(m_XOff) + ", " + std::to_string(m_YOff) + ", " + std::to_string(m_Width) + ", " + std::to_string(m_Height) + ")";
	}

}