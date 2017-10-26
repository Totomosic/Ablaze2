#include "Debugger.h"
#include "Graphics\Graphics.h"
#include "Utils\FileSystem\__FileSystem__.h"
#include "Application\Time.h"

namespace Ablaze
{

	bool Debugger::m_IsTyping = false;
	std::vector<char> Debugger::m_Command = std::vector<char>();

	void Debugger::Update()
	{
		bool done = false;
		if (m_IsTyping)
		{
			if (Input::KeyPressed(Keycode::ENTER))
			{
				ProcessCommand();
				m_IsTyping = false;
				done = true;
			}
			if (Input::KeyPressed(Keycode::BACKSPACE) && m_Command.size() > 0)
			{
				m_Command.pop_back();
				String str = ToString();
				for (int i = 0; i < str.length() + 1; i++)
				{
					std::cout << " ";
				}
				std::cout << "\r";
				std::cout << str << "\r";
			}
			for (char c : Input::CharsPressed())
			{
				InsertChar(c);
			}
		}

		if (!m_IsTyping && !done)
		{
			if (Input::KeyPressed(Keycode::ENTER))
			{
				m_IsTyping = true;
			}
		}

	}

	void Debugger::ProcessCommand()
	{
		String text = ToString();
		std::cout << std::endl;
		if (strstr(text.c_str(), "("))
		{
			std::vector<String> pieces = SplitString(text, "(");
			String command = pieces[0];
			String args = pieces[1];
			args.erase(args.end() - 1); // Remove trailing bracket
			std::vector<String> argList = SplitString(args, ",");

			if (command == "Log")
			{
				AB_INFO(args);
			}
			else if (command == "Warn")
			{
				AB_WARN(args);
			}
			else if (command == "Error")
			{
				AB_ERROR(args);
			}
			else if (command == "Fatal")
			{
				AB_FATAL(args);
			}
			else if (command == "Quit")
			{
				Graphics::CurrentContext()->Close();
			}
			else if (command == "WriteFile")
			{
				argList[1].erase(argList[1].begin(), std::find_if(argList[1].begin(), argList[1].end(), std::bind1st(std::not_equal_to<char>(), ' ')));
				File f = FileSystem::Open(argList[0], OpenMode::WriteOverride);
				FileSystem::WriteText(f, argList[1]);
				f.Close();
			}
			else if (command == "ReadFile")
			{
				File f = FileSystem::Open(args, OpenMode::Read);
				std::cout << FileSystem::ReadText(f) << std::endl;
				f.Close();
			}
			else if (command == "DeleteFile")
			{
				FileSystem::Delete(args);
			}
			else if (command == "Clear")
			{
				system("cls");
			}
			else if (command == "ClearColor")
			{
				Graphics::CurrentContext()->SetClearColor(Color(std::stoi(argList[0]), std::stoi(argList[1]), std::stoi(argList[2]), std::stoi(argList[3])));
			}
			else if (command == "ClearColorHSB")
			{
				Graphics::CurrentContext()->SetClearColor(Color::FromHSB(std::stof(argList[0]), std::stof(argList[1]), std::stof(argList[2])));
			}
			else if (command == "GameTime")
			{
				AB_INFO("GameTime: " + std::to_string(Time::TotalTime()) + "s");
			}
			else if (command == "Bytecode")
			{
				bool debug = false;
				String file = args;
				if (argList.size() == 2)
				{
					debug = (bool)std::stoi(argList[1]);
					file = argList[0];
				}
				VM::VirtualMachine vm(file, debug);
				vm.Execute();
			}
			else if (command == "Assemble")
			{
				VM::VMassembler a(argList[0]);
				a.Assemble(CleanString(argList[1]));
			}
			else if (command == "aexec")
			{
				bool debug = false;
				std::vector<String> parts = SplitString(argList[0], ".");
				String outFile = parts[0] + ".byte";
				if (argList.size() == 2)
				{
					outFile = argList[1];
				}
				if (argList.size() == 3)
				{
					outFile = argList[1];
					debug = (bool)std::stoi(argList[2]);
				}
				VM::VMassembler a(argList[0]);
				a.Assemble(CleanString(outFile));
				VM::VirtualMachine vm(CleanString(outFile), debug);
				vm.Execute();
			}
			else if (command == "Help")
			{
				AB_INFO("Available Commands: Log(msg), Warn(msg), Error(msg), Fatal(msg), Quit(), WriteFile(filename, text), ReadFile(filename), DeleteFile(filename), Clear(), ClearColor(r, g, b, a), ClearColorHSB(h, s, b), GameTime(), Bytecode(filename, debug = 0), Assemble(filename, outfile), aexec(filename, outfile = null, debug = 0), Help()");
			}
			else
			{
				AB_WARN("Invalid Command: " + text + ", Use Help()");
			}
		}
		else
		{
			AB_WARN("Invalid Command: " + text + ", Use Help()");
		}

		SetupConsole(AB_LOG_LEVEL_INFO);
		m_Command.clear();
	}

	void Debugger::InsertChar(char c)
	{
		m_Command.push_back(c);
		std::cout << ToString() << "\r";
	}

	String Debugger::ToString()
	{
		std::stringstream s;
		for (char c : m_Command)
		{
			s << c;
		}
		return s.str();
	}

}