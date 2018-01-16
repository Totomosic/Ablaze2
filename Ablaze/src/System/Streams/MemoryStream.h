#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API MemoryStream : public Object
	{
	private:
		char* m_Buffer;
		uint32_t m_Capacity;
		uint32_t m_WriteHead;

	public:
		MemoryStream(char* buffer, uint32_t byteCount);
		MemoryStream(uint32_t capacity);
		MemoryStream();
		~MemoryStream();

		char* GetBufferPtr() const;
		uint32_t GetRemainingDataSize() const;

		void Read(void* outData, uint32_t byteCount);
		void Write(const void* data, uint32_t byteCount);

		template<typename T>
		void Read(T* outValue)
		{
			AB_ASSERT(std::is_arithmetic<T>::value || std::is_enum<T>::value, "Generic read only supports primitive types");
			Read(outValue, sizeof(T));
		}

		template<typename T>
		void Write(T data)
		{
			AB_ASSERT(std::is_arithmetic<T>::value || std::is_enum<T>::value, "Generic write only supports primitive types");
			Write(&data, sizeof(T));
		}

		String ToString() const override;

	private:
		void ReallocBuffer(uint32_t newLength);
		void RealignBuffer(uint32_t offset, uint32_t length);

	};

}