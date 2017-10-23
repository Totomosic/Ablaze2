#include "VMStack.h"

namespace Ablaze
{
	namespace VM
	{

		VMStack::VMStack(int maxSize) : Object(),
			m_MaxSize(maxSize), m_Stack(new VMValue*[m_MaxSize]), m_StackPtr(-1)
		{
		
		}

		VMStack::~VMStack()
		{
			delete[] m_Stack;
		}

		VMValue* VMStack::Pop()
		{
			return m_Stack[m_StackPtr--];
		}

		void VMStack::Push(VMValue* value)
		{
			m_Stack[++m_StackPtr] = value;
		}

		VMValue* VMStack::Load(int offset)
		{
			return m_Stack[m_StackPtr + offset];
		}

		void VMStack::Reset()
		{
			delete[] m_Stack;
			m_Stack = new VMValue*[m_MaxSize];	
			m_StackPtr = -1;
		}

		String VMStack::ToString() const
		{
			return "VMStack";
		}

	}
}