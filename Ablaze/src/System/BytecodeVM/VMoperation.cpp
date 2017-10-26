#include "VMoperation.h"

namespace Ablaze
{
	namespace VM
	{

		VMoperation::VMoperation(const String& opName, VMopcode opCode, VMopfunc funcPtr, int argCount, VMtype* types)
			: opName(opName), opCode(opCode), funcPtr(funcPtr), argCount(argCount), argTypes(types)
		{
			
		}

		VMoperation::VMoperation() : VMoperation("", INT_LITERAL, Inst_IntLiteral, 1, new VMtype[1]{ INT })
		{
		
		}

		VMoperation::~VMoperation()
		{
			delete[] argTypes;
		}

		int* VMoperation::operator()(int* ip, VMstack* stack, int* code)
		{
			return funcPtr(ip, stack, code);
		}

	}
}