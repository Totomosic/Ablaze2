#pragma once
#include "Instructions.h"

namespace Ablaze
{
	namespace VM
	{

		typedef int*(*VMopfunc)(int*, VMstack*, int*);

		struct VMoperation
		{
		public:
			String opName;
			VMopcode opCode;
			VMopfunc funcPtr;
			int argCount;
			VMtype* argTypes;

		public:
			VMoperation();
			VMoperation(const String& opName, VMopcode opCode, VMopfunc funcPtr, int argCount, VMtype* types);
			~VMoperation();

			int* operator()(int* ip, VMstack* stack, int* code);

		};

	}
}