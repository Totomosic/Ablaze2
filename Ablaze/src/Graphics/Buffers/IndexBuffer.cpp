#include "IndexBuffer.h"

namespace Ablaze
{
	IndexBuffer::IndexBuffer(int64 byteSize, BufferUsage usage) : Buffer(byteSize, BufferTarget::ElementBuffer, usage)
	{

	}

	IndexBuffer::IndexBuffer(void* buffer, int64 numBytes, BufferUsage usage) : Buffer(buffer, numBytes, BufferTarget::ElementBuffer, usage)
	{
	
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