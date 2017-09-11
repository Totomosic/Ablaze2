#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API Viewport : public Object
	{
	private:
		int m_XOff;
		int m_YOff;
		int m_Width;
		int m_Height;

	public:
		Viewport(int x, int y, int width, int height);
		Viewport(int width, int height);

		int GetX() const;
		int GetY() const;
		int GetWidth() const;
		int GetHeight() const;
		float GetAspect() const;

		void SetX(int x);
		void SetY(int y);
		void SetWidth(int width);
		void SetHeight(int height);

		void Bind() const;
		void Unbind() const;

		String ToString() const override;

	};

}