#pragma once
#include "Common.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Ablaze
{

	enum class RenderMode : GLenum
	{
		Triangles = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP,
		Quads = GL_QUADS,
		TriangleFan = GL_TRIANGLE_FAN,
		Lines = GL_LINES,
		LineStrip = GL_LINE_STRIP
	};

	class AB_API VertexArray : public GLObject
	{
	private:
		std::vector<VertexBuffer*> m_VertexBuffers;
		std::vector<IndexBuffer*> m_IndexBuffers;
		RenderMode m_RenderMode;
		int64 m_VertexCount;
		int64 m_RenderCount;

		int m_CurrentIndexBuffer;

	public:
		VertexArray(RenderMode renderMode = RenderMode::Triangles);
		VertexArray(IndexBuffer* indexBuffer, RenderMode renderMode = RenderMode::Triangles);
		~VertexArray() override;

		const std::vector<VertexBuffer*>& GetVertexBuffers() const;
		const std::vector<IndexBuffer*>& GetIndexBuffers() const;
		IndexBuffer* GetIndexBuffer(int index) const;
		VertexBuffer* GetVertexBuffer(int index) const;
		bool HasIndexBuffer() const;
		bool HasVertexBuffer() const;
		int VertexBufferCount() const;
		int IndexBufferCount() const;
		int CurrentIndexBufferIndex() const;
		int64 VertexCount() const;
		int64 RenderCount() const;
		RenderMode GetRenderMode() const;

		void SetCurrentIndexBuffer(int index);
		void Bind() const override;
		void Unbind() const override;

		void AddIndexBuffer(IndexBuffer* indexBuffer);
		void RemoveIndexBuffer(int index);
		void AddVertexBuffer(VertexBuffer* vertexBuffer);
		void RemoveVertexBuffer(int index);
		void SetRenderMode(RenderMode renderMode);
		void SetVertexBuffer(int index, VertexBuffer* buffer);
		void SetIndexBuffer(int index, IndexBuffer* buffer);

		VertexBuffer* CreateAttribute(int64 byteSize, const BufferLayout& layout = BufferLayout::Default(), BufferUsage usage = BufferUsage::StaticDraw);
		VertexBuffer* CreateAttribute(void* buffer, int64 numBytes, const BufferLayout& layout = BufferLayout::Default(), BufferUsage usage = BufferUsage::StaticDraw);
		IndexBuffer* CreateIndexBuffer(int64 byteSize, IndexType type = IndexType::UnsignedInt, BufferUsage usage = BufferUsage::StaticDraw);
		IndexBuffer* CreateIndexBuffer(void* buffer, int64 numBytes, IndexType type = IndexType::UnsignedInt, BufferUsage = BufferUsage::StaticDraw);

		String ToString() const override;

	private:
		void DetermineVertexCount(VertexBuffer* buffer);
		void DetermineRenderCount();
		void TestVertexCount(VertexBuffer* buffer);

	};

}