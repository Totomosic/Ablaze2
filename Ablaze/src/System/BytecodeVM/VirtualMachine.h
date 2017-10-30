#pragma once
#include "Common.h"
#include "VMstack.h"
#include "VMoperation.h"

namespace Ablaze
{
	namespace VM
	{

		class AB_API VirtualMachine : public Object
		{
		private:
			static VMoperation** s_Ops;

		private:
			VMstack m_Stack;

			int* m_Bytecode;
			int* m_Ip;

			bool m_TraceStack;

		public:
			VirtualMachine(int* code, bool traceStack = false);
			VirtualMachine(const String& codeFile, bool traceStack = false);
			~VirtualMachine();

			void Execute();
			void SetProgram(int* code);
			void ResetProgram();

			String ToString() const override;

			friend class Engine;

		public:
			static VMoperation** GetOperations();
			static VMoperation& FindOperation(VMopcode opcode);
			static VMoperation& FindOperation(const String& opName);

		private:
			static void Initialise();

		private:
			int* LoadFile(const String& file);
			void StoreValue(std::vector<int>* code, const String& arg, VMtype type);

		};

	}
}