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
		if (s_CurrentlyBound != this)
		{
			Buffer::Bind();
			s_CurrentlyBound = this;
		}
	}

	void IndexBuffer::Unbind() const
	{
		Buffer::Unbind();
	}

} 