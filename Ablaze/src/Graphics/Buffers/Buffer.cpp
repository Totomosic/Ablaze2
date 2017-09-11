#include "Buffer.h"

namespace Ablaze
{

	Buffer::Buffer(int64 byteSize, BufferTarget target, BufferUsage usage) : GLObject(),
		m_ByteSize(byteSize), m_Target(target), m_Usage(usage)
	{
		GenBuffer();
		CreateBuffer(nullptr);
	}

	Buffer::Buffer(void* buffer, int64 numBytes, BufferTarget target, BufferUsage usage) : GLObject(),
		m_ByteSize(numBytes), m_Target(target), m_Usage(usage)
	{
		GenBuffer();
		CreateBuffer(buffer);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	int64 Buffer::GetSize() const
	{
		return m_ByteSize;
	}

	BufferTarget Buffer::GetTarget() const
	{
		return m_Target;
	}

	BufferUsage Buffer::GetUsage() const
	{
		return m_Usage;
	}

	void Buffer::Bind() const
	{
		glBindBuffer((GLenum)m_Target, m_Id);
	}

	void Buffer::Unbind() const
	{
		// Does nothing
	}

	void Buffer::Recreate()
	{
		CreateBuffer();
	}

	void Buffer::Clear()
	{
		Recreate();
	}

	void Buffer::Resize(int64 newSize)
	{
		m_ByteSize = newSize;
		Recreate();
	}

	void Buffer::Upload(const void* const buffer, int64 numBytes, int64 offset) const
	{
		Bind();
		glBufferSubData((GLenum)m_Target, offset, numBytes, buffer);
	}

	void Buffer::Upload(const void* const buffer, int64 numBytes) const
	{
		Upload(buffer, numBytes, 0);
	}

	void Buffer::Download(void* buffer, int64 numBytes, int64 offset) const
	{
		Bind();
		glGetBufferSubData((GLenum)m_Target, offset, numBytes, buffer);
	}

	void Buffer::Download(void* buffer, int64 numBytes) const
	{
		Download(buffer, numBytes, 0);
	}

	void Buffer::Download(void* buffer) const
	{
		Download(buffer, GetSize());
	}

	void* Buffer::Map(AccessMode access) const
	{
		Bind();
		return glMapBuffer((GLenum)m_Target, (GLenum)access);
	}

	bool Buffer::Unmap() const
	{
		return glUnmapBuffer((GLenum)m_Target);
	}

	String Buffer::ToString() const
	{
		return "Buffer";
	}

	void Buffer::GenBuffer()
	{
		glGenBuffers(1, &m_Id);
	}

	void Buffer::CreateBuffer(void* buffer)
	{
		Bind();
		glBufferData((GLenum)m_Target, GetSize(), buffer, (GLenum)m_Usage);
	}
	
}