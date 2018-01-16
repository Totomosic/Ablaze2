#include "MemoryStream.h"

namespace Ablaze
{

	MemoryStream::MemoryStream(char* buffer, uint32_t byteCount) : Object(),
		m_Buffer(buffer), m_Capacity(byteCount), m_WriteHead(0)
	{
	
	}

	MemoryStream::MemoryStream(uint32_t byteCount) : MemoryStream(nullptr, byteCount)
	{
		ReallocBuffer(byteCount);
	}

	MemoryStream::MemoryStream() : MemoryStream(32)
	{

	}

	MemoryStream::~MemoryStream()
	{
		std::free(m_Buffer);
	}

	char* MemoryStream::GetBufferPtr() const
	{
		return m_Buffer;
	}

	uint32_t MemoryStream::GetRemainingDataSize() const
	{
		return m_WriteHead;
	}

	void MemoryStream::Read(void* outData, uint32_t byteCount)
	{
		AB_ASSERT(byteCount <= GetRemainingDataSize(), "Stream has run out of data");
		memcpy(outData, m_Buffer, byteCount);
		RealignBuffer(byteCount, m_Capacity - byteCount);
	}

	void MemoryStream::Write(const void* data, uint32_t byteCount)
	{
		uint32_t newHead = m_WriteHead + byteCount;
		if (newHead > m_Capacity)
		{
			ReallocBuffer(max(m_Capacity * 2, newHead));
		}
		memcpy(m_Buffer + m_WriteHead, data, byteCount);
		m_WriteHead = newHead;
	}

	String MemoryStream::ToString() const
	{
		return "MemoryStream";
	}

	void MemoryStream::ReallocBuffer(uint32_t newLength)
	{
		m_Buffer = static_cast<char*>(std::realloc(m_Buffer, newLength));
		m_Capacity = newLength;
	}

	void MemoryStream::RealignBuffer(uint32_t offset, uint32_t length)
	{
		memcpy(m_Buffer + 0, m_Buffer + offset, length);
		m_WriteHead -= offset;
	}

}