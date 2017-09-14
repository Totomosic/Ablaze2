#pragma once
#include "Buffer.h"
#include "BufferLayout.h"

namespace Ablaze
{

	class AB_API VertexBuffer : public Buffer
	{
	private:
		static const VertexBuffer* s_CurrentlyBound;

	private:
		BufferLayout m_Layout;

	public:
		VertexBuffer(int64 byteSize, const BufferLayout& layout = BufferLayout::Default(), BufferUsage usage = BufferUsage::StaticDraw);
		VertexBuffer(void* buffer, int64 numBytes, const BufferLayout& layout = BufferLayout::Default(), BufferUsage usage = BufferUsage::StaticDraw);

		void Bind() const override;
		void Unbind() const override;

		const BufferLayout& GetLayout() const;
		BufferLayout& GetLayout();
		void SetLayout(const BufferLayout& layout);
		void ApplyLayout() const;

	};

}