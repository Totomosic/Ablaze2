#include "VertexArray.h"

namespace Ablaze
{

	const VertexArray* VertexArray::s_CurrentlyBound = nullptr;

	VertexArray::VertexArray(RenderMode renderMode) : GLObject(),
		m_VertexBuffers(), m_IndexBuffer(nullptr), m_RenderMode(renderMode), m_VertexCount(0), m_RenderCount(0)
	{
		GL_CALL(glGenVertexArrays(1, &m_Id));
	}

	VertexArray::VertexArray(IndexBuffer* indexBuffer, RenderMode renderMode) : VertexArray(renderMode)
	{
		SetIndexBuffer(indexBuffer);
	}

	VertexArray::~VertexArray()
	{
		for (VertexBuffer* vertexBuffer : m_VertexBuffers)
		{
			delete vertexBuffer;
		}
		if (m_IndexBuffer != nullptr)
		{
			delete m_IndexBuffer;
		}
		GL_CALL(glDeleteVertexArrays(1, &m_Id));
	}

	const std::vector<VertexBuffer*>& VertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	IndexBuffer* VertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	VertexBuffer* VertexArray::GetVertexBuffer(int index) const
	{
		return m_VertexBuffers[index];
	}

	bool VertexArray::HasIndexBuffer() const
	{
		return m_IndexBuffer != nullptr;
	}

	bool VertexArray::HasVertexBuffer() const
	{
		return m_VertexBuffers.size() != 0;
	}

	int VertexArray::VertexBufferCount() const
	{
		return (int)m_VertexBuffers.size();
	}

	int64 VertexArray::VertexCount() const
	{
		return m_VertexCount;
	}

	int64 VertexArray::RenderCount() const
	{
		return m_RenderCount;
	}

	RenderMode VertexArray::GetRenderMode() const
	{
		return m_RenderMode;
	}

	void VertexArray::Bind() const
	{
		if (s_CurrentlyBound != this)
		{
			GL_CALL(glBindVertexArray(m_Id));
			if (HasIndexBuffer())
			{
				m_IndexBuffer->Bind();
			}
			s_CurrentlyBound = this;
		}
	}

	void VertexArray::Unbind() const
	{
		// Does nothing
	}

	void VertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
		DetermineRenderCount();
	}

	void VertexArray::RemoveIndexBuffer()
	{
		delete m_IndexBuffer;
		m_IndexBuffer = nullptr;
		DetermineRenderCount();
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
			DetermineVertexCount();
		}
	}

	void VertexArray::RemoveVertexBuffer(int index)
	{
		if (index < m_VertexBuffers.size())
		{
			auto it = std::find(m_VertexBuffers.begin(), m_VertexBuffers.end(), m_VertexBuffers[index]);
			m_VertexBuffers.erase(it);
		}
	}

	void VertexArray::SetRenderMode(RenderMode renderMode)
	{
		m_RenderMode = renderMode;
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

	IndexBuffer* VertexArray::CreateIndexBuffer(int64 byteSize, BufferUsage usage)
	{
		IndexBuffer* ibo = new IndexBuffer(byteSize, usage);
		SetIndexBuffer(ibo);
		return ibo;
	}

	IndexBuffer* VertexArray::CreateIndexBuffer(void* buffer, int64 byteSize, BufferUsage usage)
	{
		IndexBuffer* ibo = new IndexBuffer(buffer, byteSize, usage);
		SetIndexBuffer(ibo);
		return ibo;
	}

	String VertexArray::ToString() const
	{
		return "Vertex Array";
	}

	const VertexArray* VertexArray::CurrentlyBound()
	{
		return s_CurrentlyBound;
	}

	void VertexArray::DetermineVertexCount()
	{
		if (HasVertexBuffer())
		{
			m_VertexCount = GetVertexBuffer(0)->GetSize() / sizeof(GLfloat) / GetVertexBuffer(0)->GetLayout().CountOf(Attribute::Position);
		}
		else
		{
			AB_WARN("Vertex Array has no Vertex Buffers attached, ID: " + std::to_string(m_Id));
		}
	}

	void VertexArray::DetermineRenderCount()
	{
		if (HasIndexBuffer())
		{
			m_RenderCount = m_IndexBuffer->GetSize() / sizeof(GLuint);
		}
		else
		{
			//AB_WARN("Vertex Array has no Index buffer bound, ID: " + std::to_string(m_Id));
		}
	}

}