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
		TriangleFan = GL_TRIANGLE_FAN
	};

	class AB_API VertexArray : public GLObject
	{
	private:
		static const VertexArray* s_CurrentlyBound;

	private:
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
		RenderMode m_RenderMode;
		int64 m_VertexCount;
		int64 m_RenderCount;

	public:
		VertexArray(RenderMode renderMode = RenderMode::Triangles);
		VertexArray(IndexBuffer* indexBuffer, RenderMode renderMode = RenderMode::Triangles);
		~VertexArray() override;

		const std::vector<VertexBuffer*>& GetVertexBuffers() const;
		IndexBuffer* GetIndexBuffer() const;
		VertexBuffer* GetVertexBuffer(int index) const;
		bool HasIndexBuffer() const;
		bool HasVertexBuffer() const;
		int VertexBufferCount() const;
		int64 VertexCount() const;
		int64 RenderCount() const;
		RenderMode GetRenderMode() const;

		void Bind() const override;
		void Unbind() const override;

		void SetIndexBuffer(IndexBuffer* indexBuffer);
		void RemoveIndexBuffer();
		void AddVertexBuffer(VertexBuffer* vertexBuffer);
		void RemoveVertexBuffer(int index);
		void SetRenderMode(RenderMode renderMode);

		VertexBuffer* CreateAttribute(int64 byteSize, const BufferLayout& layout = BufferLayout::Default(), BufferUsage usage = BufferUsage::StaticDraw);
		VertexBuffer* CreateAttribute(void* buffer, int64 numBytes, const BufferLayout& layout = BufferLayout::Default(), BufferUsage usage = BufferUsage::StaticDraw);
		IndexBuffer* CreateIndexBuffer(int64 byteSize, BufferUsage usage = BufferUsage::StaticDraw);
		IndexBuffer* CreateIndexBuffer(void* buffer, int64 numBytes, BufferUsage = BufferUsage::StaticDraw);

		String ToString() const override;

	public:
		static const VertexArray* CurrentlyBound();

	private:
		void DetermineVertexCount();
		void DetermineRenderCount();

	};

}