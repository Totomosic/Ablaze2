#include "IndexBuffer.h"

namespace Ablaze
{
	IndexBuffer::IndexBuffer(int64 byteSize, IndexType type, BufferUsage usage) : Buffer(byteSize, BufferTarget::ElementBuffer, usage),
		m_DataType(type)
	{

	}

	IndexBuffer::IndexBuffer(void* buffer, int64 numBytes, IndexType type, BufferUsage usage) : Buffer(buffer, numBytes, BufferTarget::ElementBuffer, usage),
		m_DataType(type)
	{
	
	}

	IndexType IndexBuffer::DataType() const
	{
		return m_DataType;
	}

	void IndexBuffer::Bind() const
	{
		Buffer::Bind();
	}

	void IndexBuffer::Unbind() const
	{
		Buffer::Unbind();
	}

} 