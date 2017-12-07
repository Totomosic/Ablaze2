#pragma once
#include "Common.h"
#include "Application\Input\__Input__.h"
#include "System\BytecodeVM\__BytecodeVM__.h"
#include "Scene\GameObject.h"

namespace Ablaze
{

	class AB_API Debugger
	{
	private:
		static bool m_IsTyping;
		static std::vector<char> m_Command;
		static GameObject* m_CurrentGameObject;

	public:
		Debugger() = delete;

		static void Update();

	private:
		static void ProcessCommand();
		static void InsertChar(char c);
		static String ToString();

	};
	
}