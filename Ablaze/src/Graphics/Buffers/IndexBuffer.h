#pragma once
#include "Buffer.h"

namespace Ablaze
{

	class AB_API IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(int64 byteSize, BufferUsage usage = BufferUsage::StaticDraw);
		IndexBuffer(void* buffer, int64 numBytes, BufferUsage = BufferUsage::StaticDraw);

		void Bind() const override;
		void Unbind() const override;

		friend class VertexArray;

	};

}