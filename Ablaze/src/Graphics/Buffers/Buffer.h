#pragma once
#include "Common.h"

namespace Ablaze
{

	enum class BufferTarget : GLenum
	{
		ArrayBuffer = GL_ARRAY_BUFFER,
		ElementBuffer = GL_ELEMENT_ARRAY_BUFFER
	};

	enum class BufferUsage : GLenum
	{
		StaticDraw = GL_STATIC_DRAW,
		DynamicDraw = GL_DYNAMIC_DRAW,
		StreamDraw = GL_STREAM_DRAW,
		StaticRead = GL_STATIC_READ,
		DynamicRead = GL_DYNAMIC_READ,
		StreamRead = GL_STREAM_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicCopy = GL_DYNAMIC_COPY,
		StreamCopy = GL_STREAM_COPY
	};

	enum class AccessMode : GLenum
	{
		Read = GL_READ_ONLY,
		Write = GL_WRITE_ONLY,
		ReadWrite = GL_READ_WRITE
	};

	class AB_API Buffer : public GLObject
	{
	private:
		static const Buffer* s_CurrentlyBound;

	protected:
		int64 m_ByteSize;
		BufferTarget m_Target;
		BufferUsage m_Usage;

	public:
		Buffer(int64 byteSize, BufferTarget target, BufferUsage usage);
		Buffer(void* buffer, int64 numBytes, BufferTarget target, BufferUsage usage);
		~Buffer() override;

		int64 GetSize() const;
		BufferTarget GetTarget() const;
		BufferUsage GetUsage() const;

		void Bind() const override;
		void Unbind() const override;
		void Recreate();
		void Clear();
		void Resize(int64 newSize);

		void Upload(const void* const buffer, int64 numBytes, int64 offset) const;
		void Upload(const void* const buffer, int64 numBytes) const;
		void Download(void* buffer, int64 numBytes, int64 offset) const;
		void Download(void* buffer, int64 numBytes) const;
		void Download(void* buffer) const;

		void* Map(AccessMode access) const;
		bool Unmap() const;

		template<typename T>
		T* Map(AccessMode access) const
		{
			return (T*)Map(access);
		}

		String ToString() const override;

	private:
		void GenBuffer();
		void CreateBuffer(void* buffer = nullptr);

	};

}