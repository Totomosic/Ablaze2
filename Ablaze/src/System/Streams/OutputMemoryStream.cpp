#include "OutputMemoryStream.h"

namespace Ablaze
{

	OutputMemoryStream::OutputMemoryStream() : OutputMemoryStream(32)
	{
	
	}

	OutputMemoryStream::OutputMemoryStream(uint32_t capacity) : Object(),
		m_Buffer(nullptr), m_Head(0), m_Capacity(capacity)
	{
		ReallocBuffer(m_Capacity);
	}

	OutputMemoryStream::~OutputMemoryStream()
	{
		std::free(m_Buffer);
	}

	const char* OutputMemoryStream::GetBufferPtr() const
	{
		return m_Buffer;
	}

	uint32_t OutputMemoryStream::GetLength() const
	{
		return m_Head;
	}

	void OutputMemoryStream::Write(const void* data, size_t byteLength)
	{
		uint32_t newHead = m_Head + (uint32_t)byteLength;
		if (newHead > m_Capacity)
		{
			ReallocBuffer(max(m_Capacity * 2, newHead));
		}
		memcpy(m_Buffer + m_Head, data, byteLength);
		m_Head = newHead;
	}

	String OutputMemoryStream::ToString() const
	{
		return "OutputMemoryStream";
	}

	void OutputMemoryStream::ReallocBuffer(uint32_t newLength)
	{
		m_Buffer = static_cast<char*>(std::realloc(m_Buffer, newLength));
		m_Capacity = newLength;
	}

}