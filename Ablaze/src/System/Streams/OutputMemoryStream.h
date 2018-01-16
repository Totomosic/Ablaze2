#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API OutputMemoryStream : public Object
	{
	private:
		char* m_Buffer;
		uint32_t m_Head;
		uint32_t m_Capacity;

	public:
		OutputMemoryStream();
		OutputMemoryStream(uint32_t capacity);
		~OutputMemoryStream();

		const char* GetBufferPtr() const;
		uint32_t GetLength() const;

		void Write(const void* data, size_t byteSize);

		template<typename T>
		void Write(T data)
		{
			AB_ASSERT(std::is_arithmetic<T>::value || std::is_enum<T>::value, "Generic write only supports primitive data types");
			Write(&data, sizeof(T));
		}

		String ToString() const override;

	private:
		void ReallocBuffer(uint32_t newLength);

	};

}