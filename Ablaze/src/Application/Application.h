#pragma once
#include "Common.h"
#include "Graphics\__Graphics__.h"
#include "System\Engine.h"
#include "Input\Input.h"
#include "Utils\Debug\__Debug__.h"

namespace Ablaze
{

	class AB_API Application : public Object
	{
	public:
		Application();
		~Application();

		int WindowWidth();
		int WindowHeight();

		void Start();
		void UpdateDisplay();
		void Quit();

		String ToString() const override;

		virtual void Init(); // Called once
		virtual void Tick(); // Called once per second
		virtual void Update(); // Called as many times as possible
		virtual void Render(); // Called as many times as possible

	private:
		void Run();

	};

}