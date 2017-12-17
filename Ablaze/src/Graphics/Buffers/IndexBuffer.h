#pragma once
#include "Buffer.h"

namespace Ablaze
{

	enum class IndexType : GLenum
	{
		UnsignedByte = GL_UNSIGNED_BYTE,
		UnsignedShort = GL_UNSIGNED_SHORT,
		UnsignedInt = GL_UNSIGNED_INT
	};

	class AB_API IndexBuffer : public Buffer
	{
	private:
		IndexType m_DataType;

	public:
		IndexBuffer(int64 byteSize, IndexType type = IndexType::UnsignedInt, BufferUsage usage = BufferUsage::StaticDraw);
		IndexBuffer(void* buffer, int64 numBytes, IndexType type = IndexType::UnsignedInt, BufferUsage = BufferUsage::StaticDraw);

		IndexType DataType() const;

		void Bind() const override;
		void Unbind() const override;

		friend class VertexArray;

	};

}