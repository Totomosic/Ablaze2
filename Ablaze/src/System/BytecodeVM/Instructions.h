#pragma once
#include "Common.h"

namespace Ablaze
{
	namespace VM
	{

		struct VMvalue;
		class VMstack;

		enum VMtype : int
		{
			INT,
			FLOAT,
			CHAR
		};

		enum Register : int
		{
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			MAX_REGISTERS
		};

		enum VMopcode : int
		{
			 INT_LITERAL,
			 FLT_LITERAL,
			 CHR_LITERAL,

			 PUSH,
			 POP,
			 STORE,
			 GSTORE,
			 LOAD,
			 GLOAD,
			 LDARG,
			 LDREG,
			 STREG,

			 ADD,
			 SUB,
			 MUL,
			 DIV,
			 POW,
			 MOD,

			 EQL,
			 GRT,
			 LSS,
			 GEQL,
			 LEQL,

			 JMP,
			 JMPT,
			 JMPF,

			 CALL,
			 RET,
			 HALT,

			 PRINT,
			 EMIT
		};

		int* Inst_IntLiteral(int* ip, VMstack* stack, int* code);
		int* Inst_FltLiteral(int* ip, VMstack* stack, int* code);
		int* Inst_ChrLiteral(int* ip, VMstack* stack, int* code);

		int* Inst_Push(int* ip, VMstack* stack, int* code);
		int* Inst_Pop(int* ip, VMstack* stack, int* code);

		int* Inst_LDArg(int* ip, VMstack* stack, int* code);
		int* Inst_LDReg(int* ip, VMstack* stack, int* code);
		int* Inst_STReg(int* ip, VMstack* stack, int* code);

		int* Inst_Add(int* ip, VMstack* stack, int* code);
		int* Inst_Sub(int* ip, VMstack* stack, int* code);
		int* Inst_Mul(int* ip, VMstack* stack, int* code);
		int* Inst_Div(int* ip, VMstack* stack, int* code);
		int* Inst_Pow(int* ip, VMstack* stack, int* code);
		int* Inst_Mod(int* ip, VMstack* stack, int* code);

		int* Inst_Eql(int* ip, VMstack* stack, int* code);
		int* Inst_Grt(int* ip, VMstack* stack, int* code);
		int* Inst_Lss(int* ip, VMstack* stack, int* code);
		int* Inst_Leql(int* ip, VMstack* stack, int* code);
		int* Inst_Geql(int* ip, VMstack* stack, int* code);

		int* Inst_Jmp(int* ip, VMstack* stack, int* code);
		int* Inst_JmpT(int* ip, VMstack* stack, int* code);
		int* Inst_JmpF(int* ip, VMstack* stack, int* code);

		int* Inst_Call(int* ip, VMstack* stack, int* code);
		int* Inst_Ret(int* ip, VMstack* stack, int* code);

		int* Inst_Print(int* ip, VMstack* stack, int* code);
		int* Inst_Emit(int* ip, VMstack* stack, int* code);

		inline int* Inst_None(int* ip, VMstack* stack, int* code) { return ip; }

	}
}