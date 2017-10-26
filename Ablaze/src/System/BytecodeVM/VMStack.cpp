#include "VMstack.h"

namespace Ablaze
{
	namespace VM
	{

#define AB_VM_STACK_TRACE_HELP(ss, v) \
		if (v->type == INT) \
		{\
			ss << v->value.i32;\
		}\
		else if (v->type == FLOAT) \
		{\
			ss << v->value.flt;\
		}\
		else if (v->type == CHAR) \
		{\
			ss << v->value.chr;\
		}

		VMstack::VMstack(int maxSize) : Object(),
			m_MaxSize(maxSize), m_MaxRegisters((int)MAX_REGISTERS), m_Stack(new VMvalue*[m_MaxSize]), m_Registers(new VMvalue*[m_MaxRegisters]), m_StackPtr(-1), m_FramePtr(-1)
		{
			for (int i = 0; i < m_MaxRegisters; i++)
			{
				m_Registers[i] = nullptr;
			}
		}

		VMstack::~VMstack()
		{
			while (m_StackPtr >= 0)
			{
				delete Pop();
			}
			delete[] m_Stack;
		}

		VMvalue* VMstack::Pop()
		{
			return m_Stack[m_StackPtr--];
		}

		void VMstack::Push(VMvalue* value)
		{
			m_Stack[++m_StackPtr] = value;
		}

		VMvalue* VMstack::Load(int offset)
		{
			return m_Stack[m_FramePtr + offset];
		}

		void VMstack::SetFramePtr(int ptr)
		{
			m_FramePtr = ptr;
		}

		int VMstack::GetFramePtr()
		{
			return m_FramePtr;
		}

		int VMstack::GetStackPtr()
		{
			return m_StackPtr;
		}

		VMvalue* VMstack::GetRegister(Register r)
		{
			return m_Registers[r];
		}

		void VMstack::SetRegister(Register r, VMvalue* value)
		{
			m_Registers[r] = value;
		}

		void VMstack::Reset()
		{
			delete[] m_Stack;
			m_Stack = new VMvalue*[m_MaxSize];	
			m_StackPtr = -1;
		}

		String VMstack::ToString() const
		{
			std::stringstream ss;
			int max = m_StackPtr + 1;
			ss << "Stack: [ ";
			for (int i = 0; i < max; i++)
			{
				if (i != 0)
				{
					ss << ", ";
				}
				AB_VM_STACK_TRACE_HELP(ss, m_Stack[i])
			}
			ss << " ]" << std::endl;
			ss << "Registers: [ ";
			for (int i = 0; i < m_MaxRegisters; i++)
			{
				
				if (i != 0)
				{
					ss << ", ";
				}
				if (m_Registers[i] != nullptr)
				{
					AB_VM_STACK_TRACE_HELP(ss, m_Registers[i]);
				}
				else
				{
					ss << 0;
				}
			}
			ss << " ]";
			return ss.str();
		}

	}
}