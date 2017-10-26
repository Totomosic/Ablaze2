#include "VirtualMachine.h"
#include "Utils\FileSystem\__FileSystem__.h"

namespace Ablaze
{
	namespace VM
	{

		VMoperation** VirtualMachine::s_Ops = new VMoperation*[256];

		VirtualMachine::VirtualMachine(int* byteCode, bool traceStack) : Object(),
			m_Stack(1024), m_Bytecode(byteCode), m_Ip(m_Bytecode), m_TraceStack(traceStack)
		{

		}

		VirtualMachine::VirtualMachine(const String& codeFile, bool traceStack) : VirtualMachine(LoadFile(codeFile), traceStack)
		{
			
		}

		VirtualMachine::~VirtualMachine()
		{
			//delete m_Bytecode;
		}

		VMoperation** VirtualMachine::GetOperations()
		{
			return s_Ops;
		}

		void VirtualMachine::Execute()
		{
			if (m_Bytecode != nullptr)
			{
				while (*m_Ip != HALT)
				{
					m_Ip = (*(s_Ops[*m_Ip]))(m_Ip, &m_Stack, m_Bytecode);
					if (m_TraceStack)
					{
						std::cout << m_Stack.ToString() << std::endl;
					}
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

		void VirtualMachine::Initialise()
		{
			for (int i = 0; i < 256; i++)
			{
				s_Ops[i] = nullptr;
			}

			s_Ops[INT_LITERAL] = new VMoperation("int", INT_LITERAL, Inst_IntLiteral, 1, new VMtype[1]{ INT });
			s_Ops[FLT_LITERAL] = new VMoperation("flt", FLT_LITERAL, Inst_FltLiteral, 1, new VMtype[1]{ FLOAT });
			s_Ops[CHR_LITERAL] = new VMoperation("chr", CHR_LITERAL, Inst_ChrLiteral, 1, new VMtype[1]{ CHAR });

			s_Ops[PUSH] = new  VMoperation("psh", PUSH, Inst_Push, 0, new VMtype[0]{});
			s_Ops[POP] = new VMoperation("pop", POP, Inst_Pop, 0, new VMtype[0]{});
			s_Ops[LDARG] = new  VMoperation("ldarg", LDARG, Inst_LDArg, 1, new VMtype[1]{ INT });
			s_Ops[LDREG] = new  VMoperation("ldreg", LDREG, Inst_LDReg, 1, new VMtype[1]{ INT });
			s_Ops[STREG] = new VMoperation("streg", STREG, Inst_STReg, 1, new VMtype[1]{ INT });

			s_Ops[ADD] = new  VMoperation("add", ADD, Inst_Add, 0, new VMtype[0]{});
			s_Ops[SUB] = new  VMoperation("sub", SUB, Inst_Sub, 0, new VMtype[0]{});
			s_Ops[MUL] = new VMoperation("mul", MUL, Inst_Mul, 0, new VMtype[0]{});
			s_Ops[DIV] = new  VMoperation("div", DIV, Inst_Div, 0, new VMtype[0]{});
			s_Ops[POW] = new  VMoperation("pow", POW, Inst_Pow, 0, new VMtype[0]{});
			s_Ops[MOD] = new  VMoperation("mod", MOD, Inst_Mod, 0, new VMtype[0]{});

			s_Ops[EQL] = new  VMoperation("eql", EQL, Inst_Eql, 0, new VMtype[0]{});
			s_Ops[GRT] = new  VMoperation("grt", GRT, Inst_Grt, 0, new VMtype[0]{});
			s_Ops[LSS] = new VMoperation("lss", LSS, Inst_Lss, 0, new VMtype[0]{});
			s_Ops[GEQL] = new  VMoperation("geql", GEQL, Inst_Geql, 0, new VMtype[0]{});
			s_Ops[LEQL] = new  VMoperation("leql", LEQL, Inst_Leql, 0, new VMtype[0]{});

			s_Ops[JMP] = new  VMoperation("jmp", JMP, Inst_Jmp, 1, new VMtype[1]{ INT });
			s_Ops[JMPT] = new  VMoperation("jmpt", JMPT, Inst_JmpT, 1, new VMtype[1]{ INT });
			s_Ops[JMPF] = new VMoperation("jmpf", JMPF, Inst_JmpF, 1, new VMtype[1]{ INT });

			s_Ops[CALL] = new  VMoperation("call", CALL, Inst_Call, 2, new VMtype[2]{ INT, INT });
			s_Ops[RET] = new  VMoperation("ret", RET, Inst_Ret, 1, new VMtype[1]{ INT });

			s_Ops[PRINT] = new VMoperation("prnt", PRINT, Inst_Print, 0, new VMtype[0]{});
			s_Ops[EMIT] = new VMoperation("emit", EMIT, Inst_Emit, 0, new VMtype[0]{});
			s_Ops[HALT] = new VMoperation("halt", HALT, Inst_None, 0, new VMtype[0]{});
		}

		VMoperation& VirtualMachine::FindOperation(VMopcode opcode)
		{
			for (int i = 0; i < 256; i++)
			{
				if (s_Ops[i] != nullptr && s_Ops[i]->opCode == opcode)
				{
					return *(s_Ops[i]);
				}
			}
			AB_ERROR("Unable to find op: " + opcode);
			return *(s_Ops[HALT]);
		}

		VMoperation& VirtualMachine::FindOperation(const String& opName)
		{
			for (int i = 0; i < 256; i++)
			{
				if (s_Ops[i] != nullptr && s_Ops[i]->opName == opName)
				{
					return *(s_Ops[i]);
				}
			}
			AB_ERROR("Unable to find op: " + opName);
			return *(s_Ops[HALT]);
		}

		int* VirtualMachine::LoadFile(const String& file)
		{
			std::vector<int>* code = new std::vector<int>; // needs to be deleted
			File f = FileSystem::Open(file, OpenMode::Read);
			String data = FileSystem::ReadText(f);
			f.Close();

			std::vector<String> lines = SplitString(data, ";");
			bool foundHalt = false;

			for (String& s : lines)
			{
				std::vector<String> args = SplitString(s, ",");
				String op = s;
				if (args.size() > 0)
				{
					op = args[0];
				}
				VMoperation& operation = FindOperation((VMopcode)std::stoi(op));
				code->push_back((int)operation.opCode);
				for (int i = 0; i < operation.argCount; i++)
				{
					StoreValue(code, args[i + 1], operation.argTypes[i]);
				}
				if (operation.opCode == HALT)
				{
					foundHalt = true;
				}
			}

			if (!foundHalt)
			{
				AB_FATAL("No HALT (" + std::to_string(HALT) + ") command found in bytecode: " + file);
				return nullptr;
			}
			return &(*code)[0];
		}

		void VirtualMachine::StoreValue(std::vector<int>* code, const String& value, VMtype type)
		{
			if (type == INT)
			{
				int v = std::stoi(value);
				code->push_back(v);
			}
			else if (type == FLOAT)
			{
				float v = std::stof(value);
				code->push_back(*reinterpret_cast<int*>(&v));
			}
			else if (type == CHAR)
			{
				char v = *(value.end() - 1);
				code->push_back(*reinterpret_cast<int*>(&v));
			}
		}

	}
}