#pragma once
#include "Common.h"

namespace Ablaze
{
	namespace VM
	{

		struct VMValue;

		const int INT = 0x00;
		const int FLOAT = 0x01;
		const int CHAR = 0x02;

		const int INT_LITERAL = 0x00;
		const int FLT_LITERAL = 0x01;
		const int CHR_LITERAL = 0x02;

		const int POP = 0x04;
		const int STORE = 0x05;
		const int GSTORE = 0x06;
		const int LOAD = 0x07;
		const int GLOAD = 0x08;
		const int LDARG = 0x09;

		const int ADD = 0x0a;
		const int SUB = 0x0b;
		const int MUL = 0x0c;
		const int DIV = 0x0d;
		const int POW = 0x0e;
		const int MOD = 0x0f;

		const int EQL = 0x10;
		const int GRT = 0x11;
		const int LESS = 0x12;
		const int LEQL = 0x13;
		const int GEQL = 0x14;

		const int JMP = 0x15;
		const int JMPT = 0x16;
		const int JMPF = 0x17;

		const int CALL = 0x18;
		const int RET = 0x19;
		const int HALT = 0x1a;

		const int PRINT = 0x1b;

		void Inst_Print(VMValue* v);
		VMValue* Inst_Add(VMValue* l, VMValue* r);
		VMValue* Inst_Sub(VMValue* l, VMValue* r);
		VMValue* Inst_Mul(VMValue* l, VMValue* r);
		VMValue* INst_Div(VMValue* l, VMValue* r);

	}
}