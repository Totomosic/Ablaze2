#pragma once
#include "Common.h"
#include "VMStack.h"

namespace Ablaze
{
	namespace VM
	{

		class VirtualMachine : public Object
		{
		private:
			VMStack m_Stack;
			int m_Ip;

			int* m_Bytecode;

		public:
			VirtualMachine(int* code);
			VirtualMachine(const String& codeFile);
			~VirtualMachine();

			void Execute();
			void SetProgram(int* code);
			void ResetProgram();

			String ToString() const override;

		private:
			int* LoadFile(const String& file);

		};

	}
}