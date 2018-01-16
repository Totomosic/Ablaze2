#include "InputMemoryStream.h"

namespace Ablaze
{

	InputMemoryStream::InputMemoryStream(char* buffer, uint32_t byteCount) : Object(),
		m_Buffer(buffer), m_Head(0), m_Capacity(byteCount)
	{
	
	}

	InputMemoryStream::InputMemoryStream(uint32_t capacity) : InputMemoryStream(new char[capacity], capacity)
	{
	
	}

	InputMemoryStream::~InputMemoryStream()
	{
		std::free(m_Buffer);
	}

	uint32_t InputMemoryStream::GetRemainingDataSize() const
	{
		return m_Capacity - m_Head;
	}

	char* InputMemoryStream::GetBufferPtr() const
	{
		return m_Buffer;
	}

	void InputMemoryStream::Read(void* outData, uint32_t byteCount)
	{
		AB_ASSERT(byteCount <= GetRemainingDataSize(), "Stream out of data");
		memcpy(outData, m_Buffer + m_Head, byteCount);
		m_Head += byteCount;
	}

	String InputMemoryStream::ToString() const
	{
		return "InputMemoryStream";
	}

}