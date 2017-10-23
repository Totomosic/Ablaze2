#include "Instructions.h"
#include "VMValue.h"

namespace Ablaze
{
	namespace VM
	{

		void Inst_Print(VMValue* v)
		{
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
		}

		VMValue* Inst_Add(VMValue* l, VMValue* r)
		{
			VMValue* v = new VMValue;
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
			return v;
		}

		VMValue* Inst_Sub(VMValue* l, VMValue* r)
		{
			VMValue tr;
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
			return Inst_Add(l, &tr);
		}

	}
}