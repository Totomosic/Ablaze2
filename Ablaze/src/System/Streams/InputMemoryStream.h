#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API InputMemoryStream : public Object
	{
	private:
		char* m_Buffer;
		uint32_t m_Head;
		uint32_t m_Capacity;

	public:
		InputMemoryStream(char* buffer, uint32_t byteCount);
		InputMemoryStream(uint32_t capacity);
		~InputMemoryStream();

		uint32_t GetRemainingDataSize() const;
		char* GetBufferPtr() const;

		void Read(void* outData, uint32_t byteCount);
		
		template<typename T>
		void Read(T* outValue)
		{
			AB_ASSERT(std::is_arithmetic<T>::value || std::is_enum<T>::value, "Generic read only supports primitive types");
			Read(outValue, sizeof(T));
		}

		String ToString() const override;

	};

}