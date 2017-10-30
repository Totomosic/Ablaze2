#pragma once
#include "Common.h"
#include "VMvalue.h"

namespace Ablaze
{
	namespace VM
	{

		class AB_API VMstack : public Object
		{
		private:
			int m_MaxSize;
			int m_MaxRegisters;
			VMvalue** m_Stack;
			VMvalue** m_Registers;

			int m_StackPtr;
			int m_FramePtr;

		public:
			VMstack(int maxSize);
			~VMstack();

			int GetFramePtr();
			int GetStackPtr();

			VMvalue* Pop();
			void Push(VMvalue* value);
			VMvalue* Load(int offset);

			VMvalue* GetRegister(Register r);
			void SetRegister(Register r, VMvalue* value);

			void Reset();
			void SetFramePtr(int ptr);

			String ToString() const override;

		};

	}
}