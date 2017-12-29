#include "VertexArray.h"

namespace Ablaze
{

	VertexArray::VertexArray(RenderMode renderMode) : GLObject(),
		m_VertexBuffers(), m_IndexBuffers(), m_RenderMode(renderMode), m_VertexCount(0), m_RenderCount(0), m_CurrentIndexBuffer(-1)
	{
		GL_CALL(glGenVertexArrays(1, &m_Id));
	}

	VertexArray::VertexArray(IndexBuffer* indexBuffer, RenderMode renderMode) : VertexArray(renderMode)
	{
		AddIndexBuffer(indexBuffer);
	}

	VertexArray::~VertexArray()
	{
		for (VertexBuffer* vertexBuffer : m_VertexBuffers)
		{
			delete vertexBuffer;
		}
		for (IndexBuffer* indexBuffer : m_IndexBuffers)
		{
			delete indexBuffer;
		}
		GL_CALL(glDeleteVertexArrays(1, &m_Id));
	}

	const std::vector<VertexBuffer*>& VertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::vector<IndexBuffer*>& VertexArray::GetIndexBuffers() const
	{
		return m_IndexBuffers;
	}

	IndexBuffer* VertexArray::GetIndexBuffer(int index) const
	{
		return m_IndexBuffers[index];
	}

	VertexBuffer* VertexArray::GetVertexBuffer(int index) const
	{
		return m_VertexBuffers[index];
	}

	bool VertexArray::HasIndexBuffer() const
	{
		return m_IndexBuffers.size() != 0;
	}

	bool VertexArray::HasVertexBuffer() const
	{
		return m_VertexBuffers.size() != 0;
	}

	int VertexArray::VertexBufferCount() const
	{
		return (int)m_VertexBuffers.size();
	}

	int VertexArray::IndexBufferCount() const
	{
		return (int)m_IndexBuffers.size();
	}

	int64 VertexArray::VertexCount() const
	{
		return m_VertexCount;
	}

	int64 VertexArray::RenderCount() const
	{
		return m_RenderCount;
	}

	int VertexArray::CurrentIndexBufferIndex() const
	{
		return m_CurrentIndexBuffer;
	}

	RenderMode VertexArray::GetRenderMode() const
	{
		return m_RenderMode;
	}

	void VertexArray::SetCurrentIndexBuffer(int index)
	{
		m_CurrentIndexBuffer = index;
		DetermineRenderCount();
	}

	void VertexArray::Bind() const
	{
		GL_CALL(glBindVertexArray(m_Id));
		if (HasIndexBuffer())
		{
			m_IndexBuffers[m_CurrentIndexBuffer]->Bind();
		}
	}

	void VertexArray::Unbind() const
	{
		// Does nothing
	}

	void VertexArray::AddIndexBuffer(IndexBuffer* indexBuffer)
	{
		m_IndexBuffers.push_back(indexBuffer);
		if (m_CurrentIndexBuffer == -1)
		{
			m_CurrentIndexBuffer = 0;
			DetermineRenderCount();
		}		
	}

	void VertexArray::RemoveIndexBuffer(int index)
	{
		AB_ASSERT(index < m_IndexBuffers.size(), "Index Out of Range");
		IndexBuffer* ibo = m_IndexBuffers[index];
		m_IndexBuffers.erase(m_IndexBuffers.begin() + index);
		delete ibo;
	}

	void VertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer)
	{
		m_VertexBuffers.push_back(vertexBuffer);

		Bind();
		vertexBuffer->ApplyLayout();
		Unbind();

		if (m_VertexBuffers.size() == 1)
		{
			// This was the first one added
			DetermineRenderCount();
			DetermineVertexCount(vertexBuffer);
		}
		TestVertexCount(vertexBuffer);
	}

	void VertexArray::RemoveVertexBuffer(int index)
	{
		AB_ASSERT(index < m_VertexBuffers.size(), "Index Out of Range");
		VertexBuffer* vbo = m_VertexBuffers.at(index);
		m_VertexBuffers.erase(m_VertexBuffers.begin() + index);
		delete vbo;
	}

	void VertexArray::SetRenderMode(RenderMode renderMode)
	{
		m_RenderMode = renderMode;
		DetermineRenderCount();
	}

	void VertexArray::SetVertexBuffer(int index, VertexBuffer* buffer)
	{
		AB_ASSERT(index < m_VertexBuffers.size(), "Index Out of Range");
		VertexBuffer* prev = m_VertexBuffers[index];
		m_VertexBuffers[index] = buffer;
		delete prev;
		DetermineVertexCount(buffer);
	}

	void VertexArray::SetIndexBuffer(int index, IndexBuffer* buffer)
	{
		AB_ASSERT(index < m_IndexBuffers.size(), "Index Out of Range");
		IndexBuffer* prev = m_IndexBuffers[index];
		m_IndexBuffers[index] = buffer;
		delete prev;
		DetermineRenderCount();
	}

	VertexBuffer* VertexArray::CreateAttribute(int64 byteSize, const BufferLayout& layout, BufferUsage usage)
	{
		VertexBuffer* vbo = new VertexBuffer(byteSize, layout, usage);
		AddVertexBuffer(vbo);
		return vbo;
	}

	VertexBuffer* VertexArray::CreateAttribute(void* buffer, int64 byteSize, const BufferLayout& layout, BufferUsage usage)
	{
		VertexBuffer* vbo = new VertexBuffer(buffer, byteSize, layout, usage);
		AddVertexBuffer(vbo);
		return vbo;
	}

	IndexBuffer* VertexArray::CreateIndexBuffer(int64 byteSize, IndexType type, BufferUsage usage)
	{
		IndexBuffer* ibo = new IndexBuffer(byteSize, type, usage);
		AddIndexBuffer(ibo);
		return ibo;
	}

	IndexBuffer* VertexArray::CreateIndexBuffer(void* buffer, int64 byteSize, IndexType type, BufferUsage usage)
	{
		IndexBuffer* ibo = new IndexBuffer(buffer, byteSize, type, usage);
		AddIndexBuffer(ibo);
		return ibo;
	}

	String VertexArray::ToString() const
	{
		return "VertexArray";
	}

	void VertexArray::DetermineVertexCount(VertexBuffer* buffer)
	{
		m_VertexCount = buffer->GetSize() / buffer->GetLayout().GetStride();
	}

	void VertexArray::DetermineRenderCount()
	{
		if (HasIndexBuffer())
		{
			m_RenderCount = m_IndexBuffers[m_CurrentIndexBuffer]->GetSize() / sizeof(GLuint);
		}
	}

	void VertexArray::TestVertexCount(VertexBuffer* buffer)
	{
		int vertexCount = buffer->GetSize() / buffer->GetLayout().GetStride();
		if (vertexCount != m_VertexCount && m_VertexBuffers.size() > 1)
		{
			AB_WARN("Buffer added that does not match vertex count: " + std::to_string(m_VertexCount));
		}
	}

}