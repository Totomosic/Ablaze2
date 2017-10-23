#pragma once
#include "Common.h"
#include "VMValue.h"

namespace Ablaze
{
	namespace VM
	{

		class VMStack : public Object
		{
		private:
			int m_MaxSize;
			VMValue** m_Stack;
			int m_StackPtr;

		public:
			VMStack(int maxSize);
			~VMStack();

			VMValue* Pop();
			void Push(VMValue* value);

			VMValue* Load(int offset);
			void Reset();

			String ToString() const override;

		};

	}
}