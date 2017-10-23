#include "VirtualMachine.h"
#include "Utils\FileSystem\__FileSystem__.h"

namespace Ablaze
{
	namespace VM
	{

		VirtualMachine::VirtualMachine(int* byteCode) : Object(),
			m_Stack(1024), m_Ip(0), m_Bytecode(byteCode)
		{
		
		}

		VirtualMachine::VirtualMachine(const String& codeFile) : VirtualMachine(LoadFile(codeFile))
		{
			
		}

		VirtualMachine::~VirtualMachine()
		{
			//delete m_Bytecode;
		}

		void VirtualMachine::Execute()
		{
			while (true)
			{
				int opCode = m_Bytecode[m_Ip];
				switch (opCode)
				{
				case INT_LITERAL:
				{
					VMValue* value = new VMValue;
					int integer = m_Bytecode[++m_Ip];
					value->type = INT;
					value->value.i32 = integer;
					m_Stack.Push(value);
					m_Ip++;
				}
				break;

				case FLT_LITERAL:
				{
					VMValue* value = new VMValue;
					int v = m_Bytecode[++m_Ip];
					float* flt = reinterpret_cast<float*>(&v);
					value->type = FLOAT;
					value->value.flt = *flt;
					m_Stack.Push(value);
					m_Ip++;
				}
				break;

				case CHR_LITERAL:
				{
					VMValue* value = new VMValue;
					int v = m_Bytecode[++m_Ip];
					char* chr = reinterpret_cast<char*>(&v);
					value->type = CHAR;
					value->value.chr = *chr;
					m_Stack.Push(value);
					m_Ip++;
				}
				break;

				case ADD:
				{
					VMValue* right = m_Stack.Pop();
					VMValue* left = m_Stack.Pop();
					m_Stack.Push(Inst_Add(left, right));
					m_Ip++;
				}
				break;

				case SUB:
				{
					VMValue* right = m_Stack.Pop();
					VMValue* left = m_Stack.Pop();
					m_Stack.Push(Inst_Sub(left, right));
					m_Ip++;
				}
				break;

				case PRINT:
				{
					VMValue* value = m_Stack.Pop();
					Inst_Print(value);
					m_Ip++;
				}
				break;

				case HALT:
					return;

				default:
				{
					AB_ERROR("Opcode was not recognised: " + std::to_string(opCode));
				}
				return;

				}
			}
		}

		void VirtualMachine::SetProgram(int* code)
		{
			m_Bytecode = code;
			m_Ip = 0;
			m_Stack.Reset();
		}

		void VirtualMachine::ResetProgram()
		{
			m_Ip = 0;
			m_Stack.Reset();
		}

		String VirtualMachine::ToString() const
		{
			return "VirtualMachine";
		}

		int* VirtualMachine::LoadFile(const String& file)
		{
			std::vector<int>* code = new std::vector<int>;
			File f = FileSystem::Open(file, OpenMode::Read);
			String data = FileSystem::ReadText(f);
			f.Close();

			std::vector<String> lines = SplitString(data, ";");

			for (String& s : lines)
			{
				if (strstr(s.c_str(), " "))
				{
					std::vector<String> args = SplitString(s, " ");
					int opCode = std::stoi(args[0]);
					if (opCode == INT_LITERAL)
					{
						code->push_back(opCode);
						code->push_back(std::stoi(args[1]));
					}
				}
				else
				{
					code->push_back(std::stoi(s));
				}
			}
			return &(*code)[0];
		}

	}
}