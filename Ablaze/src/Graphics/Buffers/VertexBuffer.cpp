#include "VertexBuffer.h"

namespace Ablaze
{

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
		Buffer::Bind();
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
			GL_CALL(glEnableVertexAttribArray(attrib.index));
			GL_CALL(glVertexAttribPointer(attrib.index, attrib.count, attrib.dataType, attrib.normalized, m_Layout.GetStride(), (const GLvoid*)attrib.offset));
		}
		Unbind();
	}

	VertexBuffer* VertexBuffer::Combine(VertexBuffer* left, VertexBuffer* right, bool preserveData)
	{
		VertexBuffer* result = new VertexBuffer(left->GetSize() + right->GetSize(), left->GetLayout(), left->GetUsage());
		if (preserveData)
		{
			byte* leftData = new byte[left->GetSize()];
			byte* rightData = new byte[right->GetSize()];
			left->Download((void*)leftData);
			right->Download((void*)rightData);
			result->Upload((const void*)leftData, left->GetSize());
			result->Upload((const void*)rightData, right->GetSize(), left->GetSize());
		}
		return result;
	}

}