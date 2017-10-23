#include "VertexBuffer.h"

namespace Ablaze
{

	const VertexBuffer* VertexBuffer::s_CurrentlyBound = nullptr;

	VertexBuffer::VertexBuffer(int64 byteSize, const BufferLayout& layout, BufferUsage usage) : Buffer(byteSize, BufferTarget::ArrayBuffer, usage),
		m_Layout(layout)
	{
		
	}

	VertexBuffer::VertexBuffer(void* buffer, int64 numBytes, const BufferLayout& layout, BufferUsage usage) : Buffer(buffer, numBytes, BufferTarget::ArrayBuffer, usage),
		m_Layout(layout)
	{
		
	}

	void VertexBuffer::Bind() const
	{
		if (s_CurrentlyBound != this)
		{
			Buffer::Bind();
			s_CurrentlyBound = this;
		}
	}

	void VertexBuffer::Unbind() const
	{
		Buffer::Unbind();
	}

	const BufferLayout& VertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	BufferLayout& VertexBuffer::GetLayout()
	{
		return m_Layout;
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
		ApplyLayout();
	}

	void VertexBuffer::ApplyLayout() const
	{
		Bind();
		for (const VertexAttrib& attrib : m_Layout.GetAllAttributes())
		{
			GL_CALL(glVertexAttribPointer(attrib.index, attrib.count, attrib.dataType, attrib.normalized, m_Layout.GetStride(), (const GLvoid*)attrib.offset));
			GL_CALL(glEnableVertexAttribArray(attrib.index));
		}
		Unbind();
	}

}