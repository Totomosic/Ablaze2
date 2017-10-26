#include "Instructions.h"
#include "VMvalue.h"
#include "VMstack.h"

namespace Ablaze
{
	namespace VM
	{

#define AB_VM_BOOL_OPERATOR(ip, stack, op) \
		VMvalue* r = stack->Pop(); \
		VMvalue* l = stack->Pop(); \
		VMvalue* v = new VMvalue;\
		v->type = INT;\
		if (l->type == INT)        \
		{\
			if (r->type == INT)\
			{\
				v->value.i32 = l->value.i32 op r->value.i32;\
			}\
			else if (r->type == FLOAT)\
			{\
				v->value.i32 = l->value.i32 op r->value.flt;\
			}\
			else if (r->type == CHAR)\
			{\
				v->value.i32 = l->value.i32 op r->value.chr;\
			}\
		}\
		else if (l->type == FLOAT)\
		{\
			if (r->type == INT)\
			{\
				v->value.i32 = l->value.flt op r->value.i32;\
			}\
			else if (r->type == FLOAT)\
			{\
				v->value.i32 = l->value.flt op r->value.flt;\
			}\
			else if (r->type == CHAR)\
			{\
				v->value.flt = l->value.flt op r->value.chr;\
			}\
		}\
		if (l->type == CHAR)\
		{\
			if (r->type == INT)\
			{\
				v->value.i32 = l->value.chr op r->value.i32;\
			}\
			else if (r->type == FLOAT)\
			{\
				v->value.flt = l->value.chr op r->value.flt;\
			}\
			else if (r->type == CHAR)\
			{\
				v->value.i32 = l->value.chr op r->value.chr;\
			}\
		}\
		stack->Push(v);\
		return ip + 1

		int* Inst_IntLiteral(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = new VMvalue;
			v->type = INT;
			v->value.i32 = *(ip + 1);
			stack->Push(v);
			return ip + 2;
		}

		int* Inst_FltLiteral(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = new VMvalue;
			v->type = FLOAT;
			int intval = *(ip + 1);
			v->value.flt = *reinterpret_cast<float*>(&intval);
			stack->Push(v);
			return ip + 2;
		}

		int* Inst_ChrLiteral(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = new VMvalue;
			v->type = CHAR;
			int intval = *(ip + 1);
			v->value.chr = *reinterpret_cast<char*>(&intval);
			stack->Push(v);
			return ip + 2;
		}

		int* Inst_Push(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = stack->Pop();
			VMvalue* newV = new VMvalue;
			newV->type = v->type;
			newV->value.i32 = v->value.i32;
			stack->Push(v);
			stack->Push(newV);
			return ip + 1;
		}

		int* Inst_Pop(int* ip, VMstack* stack, int* code)
		{
			delete stack->Pop();
			return ip + 1;
		}

		int* Inst_LDArg(int* ip, VMstack* stack, int* code)
		{
			int index = *(ip + 1);
			VMvalue* numParams = stack->Load(-2);
			VMvalue* v = stack->Load(-3 - numParams->value.i32 + index);
			stack->Push(v);
			return ip + 2;
		}

		int* Inst_LDReg(int* ip, VMstack* stack, int* code)
		{
			int reg = *(ip + 1);
			stack->Push(stack->GetRegister((Register)reg));
			return ip + 2;
		}

		int* Inst_STReg(int* ip, VMstack* stack, int* code)
		{
			int reg = *(ip + 1);
			VMvalue* val = stack->Pop();
			stack->SetRegister((Register)reg, val);
			return ip + 2;
		}

		int* Inst_Print(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = stack->Pop();
			if (v->type == INT)
			{
				std::cout << v->value.i32 << std::endl;
			}
			else if (v->type == FLOAT)
			{
				std::cout << v->value.flt << std::endl;
			}
			else if (v->type == CHAR)
			{
				std::cout << v->value.chr << std::endl;
			}
			return ip + 1;
		}

		int* Inst_Emit(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = stack->Pop();
			if (v->type == INT)
			{
				std::cout << v->value.i32;
			}
			else if (v->type == FLOAT)
			{
				std::cout << v->value.flt;
			}
			else if (v->type == CHAR)
			{
				std::cout << v->value.chr;
			}
			return ip + 1;
		}

		int* Inst_Add(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = new VMvalue;
			VMvalue* r = stack->Pop();
			VMvalue* l = stack->Pop();
			if (l->type == INT)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = l->value.i32 + r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.i32 + r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = INT;
					v->value.i32 = l->value.i32 + r->value.chr;
				}
			}
			else if (l->type == FLOAT)
			{
				if (r->type == INT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt + r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt + r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt + r->value.chr;
				}
			}
			if (l->type == CHAR)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = l->value.chr + r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.chr + r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = CHAR;
					v->value.i32 = l->value.chr + r->value.chr;
				}
			}
			stack->Push(v);
			return ip + 1;
		}

		int* Inst_Sub(int* ip, VMstack* stack, int* code)
		{
			VMvalue tr;
			VMvalue* r = stack->Pop();
			VMvalue* l = stack->Pop();
			tr.type = r->type;
			if (tr.type == INT)
			{
				tr.value.i32 = -r->value.i32;
			}
			else if (tr.type == FLOAT)
			{
				tr.value.flt = -r->value.flt;
			}
			else if (tr.type == CHAR)
			{
				tr.value.chr = -r->value.chr;
			}
			stack->Push(l);
			stack->Push(&tr);
			return Inst_Add(ip, stack, code);
		}

		int* Inst_Mul(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = new VMvalue;
			VMvalue* r = stack->Pop();
			VMvalue* l = stack->Pop();
			if (l->type == INT)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = l->value.i32 * r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.i32 * r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = INT;
					v->value.i32 = l->value.i32 * r->value.chr;
				}
			}
			else if (l->type == FLOAT)
			{
				if (r->type == INT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt * r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt * r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt * r->value.chr;
				}
			}
			if (l->type == CHAR)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = l->value.chr * r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.chr * r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = CHAR;
					v->value.i32 = l->value.chr * r->value.chr;
				}
			}
			stack->Push(v);
			return ip + 1;
		}

		int* Inst_Div(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = new VMvalue;
			VMvalue* r = stack->Pop();
			VMvalue* l = stack->Pop();
			if (l->type == INT)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = l->value.i32 / r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.i32 / r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = INT;
					v->value.i32 = l->value.i32 / r->value.chr;
				}
			}
			else if (l->type == FLOAT)
			{
				if (r->type == INT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt / r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt / r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = FLOAT;
					v->value.flt = l->value.flt / r->value.chr;
				}
			}
			if (l->type == CHAR)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = l->value.chr / r->value.i32;
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = l->value.chr / r->value.flt;
				}
				else if (r->type == CHAR)
				{
					v->type = CHAR;
					v->value.i32 = l->value.chr / r->value.chr;
				}
			}
			stack->Push(v);
			return ip + 1;
		}

		int* Inst_Pow(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = new VMvalue;
			VMvalue* r = stack->Pop();
			VMvalue* l = stack->Pop();
			if (l->type == INT)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = (int)pow(l->value.i32, r->value.i32);
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = (float)pow(l->value.i32, r->value.flt);
				}
				else if (r->type == CHAR)
				{
					v->type = INT;
					v->value.i32 = (int)pow(l->value.i32, r->value.chr);
				}
			}
			else if (l->type == FLOAT)
			{
				if (r->type == INT)
				{
					v->type = FLOAT;
					v->value.flt = (float)pow(l->value.flt, r->value.i32);
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = (float)pow(l->value.flt, r->value.flt);
				}
				else if (r->type == CHAR)
				{
					v->type = FLOAT;
					v->value.flt = (float)pow(l->value.flt, r->value.chr);
				}
			}
			if (l->type == CHAR)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = (int)pow(l->value.chr, r->value.i32);
				}
				else if (r->type == FLOAT)
				{
					v->type = FLOAT;
					v->value.flt = (float)pow(l->value.chr, r->value.flt);
				}
				else if (r->type == CHAR)
				{
					v->type = CHAR;
					v->value.i32 = (int)pow(l->value.chr, r->value.chr);
				}
			}
			stack->Push(v);
			return ip + 1;
		}

		int* Inst_Mod(int* ip, VMstack* stack, int* code)
		{
			VMvalue* v = new VMvalue;
			VMvalue* r = stack->Pop();
			VMvalue* l = stack->Pop();
			if (l->type == INT)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = l->value.i32 % r->value.i32;
				}
				else if (r->type == CHAR)
				{
					v->type = INT;
					v->value.i32 = l->value.i32 % r->value.chr;
				}
				else
				{
					AB_ERROR("Value was not integral type for mod");
				}
			}
			else if (l->type == CHAR)
			{
				if (r->type == INT)
				{
					v->type = INT;
					v->value.i32 = l->value.chr % r->value.i32;
				}
				else if (r->type == CHAR)
				{
					v->type = CHAR;
					v->value.i32 = l->value.chr % r->value.chr;
				}
				else
				{
					AB_ERROR("Value was not integral type for mod");
				}
			}
			else
			{
				AB_ERROR("Value was not integral type for mod");
			}
			stack->Push(v);
			return ip + 1;
		}

		int* Inst_Eql(int* ip, VMstack* stack, int* code)
		{
			AB_VM_BOOL_OPERATOR(ip, stack, ==);
		}

		int* Inst_Grt(int* ip, VMstack* stack, int* code)
		{
			AB_VM_BOOL_OPERATOR(ip, stack, >);
		}

		int* Inst_Lss(int* ip, VMstack* stack, int* code)
		{
			AB_VM_BOOL_OPERATOR(ip, stack, <);
		}

		int* Inst_Geql(int* ip, VMstack* stack, int* code)
		{
			AB_VM_BOOL_OPERATOR(ip, stack, >=);
		}

		int* Inst_Leql(int* ip, VMstack* stack, int* code)
		{
			AB_VM_BOOL_OPERATOR(ip, stack, <=);
		}

		int* Inst_Jmp(int* ip, VMstack* stack, int* code)
		{
			int addr = *(ip + 1);
			return code + addr;
		}

		int* Inst_JmpT(int* ip, VMstack* stack, int* code)
		{
			VMvalue* exp = stack->Pop();
			if (exp->type == INT)
			{
				if (exp->value.i32)
				{
					return Inst_Jmp(ip, stack, code);
				}
			}
			else if (exp->type == FLOAT)
			{
				if (exp->value.flt)
				{
					return Inst_Jmp(ip, stack, code);
				}
			}
			else if (exp->type == CHAR)
			{
				if (exp->value.chr)
				{
					return Inst_Jmp(ip, stack, code);
				}
			}
			return ip + 2;
		}

		int* Inst_JmpF(int* ip, VMstack* stack, int* code)
		{
			int addr = *(ip + 1);
			VMvalue* exp = stack->Pop();
			if (exp->type == INT)
			{
				if (!exp->value.i32)
				{
					return Inst_Jmp(ip, stack, code);
				}
			}
			else if (exp->type == FLOAT)
			{
				if (!exp->value.flt)
				{
					return Inst_Jmp(ip, stack, code);
				}
			}
			else if (exp->type == CHAR)
			{
				if (!exp->value.chr)
				{
					return Inst_Jmp(ip, stack, code);
				}
			}
			return ip + 2;
		}

		int* Inst_Call(int* ip, VMstack* stack, int* code)
		{
			int faddr = *(ip + 1);
			int paramCount = *(ip + 2);
			VMvalue* retAddr = new VMvalue;
			retAddr->type = INT;
			retAddr->value.i32 = (int)(ip + 3 - code);
			stack->Push(retAddr); // Push return address
			VMvalue* pCount = new VMvalue;
			pCount->type = INT;
			pCount->value.i32 = paramCount;
			stack->Push(pCount);
			VMvalue* prevFP = new VMvalue;
			prevFP->type = INT;
			prevFP->value.i32 = stack->GetFramePtr();
			stack->Push(prevFP);
			stack->SetFramePtr(stack->GetStackPtr() + 1); // Set the fp to the current sp
			return code + faddr;
		}

		int* Inst_Ret(int* ip, VMstack* stack, int* code)
		{
			int retCount = *(ip + 1);
			std::vector<VMvalue*> retvals;
			for (int i = 0; i < retCount; i++)
			{
				retvals.push_back(stack->Pop());
			}
			// Assume that the stack is now empty (except for fp, ret addr)
			VMvalue* prevFP = stack->Pop();
			VMvalue* paramCount = stack->Pop();
			VMvalue* retAddr = stack->Pop();
			for (int i = 0; i < paramCount->value.i32; i++)
			{
				delete stack->Pop();
			}
			stack->SetFramePtr(prevFP->value.i32);
			int addr = retAddr->value.i32;
			for (VMvalue* val : retvals)
			{
				stack->Push(val);
			}
			return code + addr;
		}

	}
}