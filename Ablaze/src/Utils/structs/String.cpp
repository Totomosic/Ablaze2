#include "String.h"

#if USE_ABLAZE_STRING

namespace Ablaze
{

	String::String(const char* str)
		: m_Ptr(str), m_Size(0)
	{
		m_Size = CalcSize(m_Ptr);
	}

	String::String() : String("")
	{

	}

	String::String(const String& other)
		: m_Ptr(new const char[other.m_Size * sizeof(char)]), m_Size(other.m_Size)
	{
		memcpy((void*)m_Ptr, other.m_Ptr, other.m_Size * sizeof(char));
	}

	String::String(const std::string& other)
		: m_Ptr(other.c_str()), m_Size(other.length())
	{
		
	}

	String::~String()
	{
		delete[] m_Ptr;
	}

	int String::size() const
	{
		return m_Size;
	}

	int String::length() const
	{
		return size();
	}

	const char* String::c_str() const
	{
		return m_Ptr;
	}

	bool String::empty() const
	{
		return m_Size == 0;
	}

	char String::operator[](int index) const
	{
		return m_Ptr[index];
	}

	String String::operator+(const String& other) const
	{
		char* buffer = new char[(size() + other.size()) * sizeof(char)];
		memcpy(buffer, m_Ptr, size() * sizeof(char));
		buffer += size();
		memcpy(buffer, other.m_Ptr, other.size() * sizeof(char));
		return String(buffer);
	}

	String String::operator+(const char* other) const
	{
		return *this + String(other);
	}

	bool String::operator==(const String& other) const
	{
		if (size() != other.size())
		{
			return false;
		}
		return CompareElements(m_Ptr, other.m_Ptr, size());
	}

	bool String::operator!=(const String& other) const
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const String& string)
	{
		stream << string.m_Ptr;
		return stream;
	}

	String operator+(const char* ptr, const String& str)
	{
		int ptrSize = String::CalcSize(ptr);
		char* buffer = new char[(str.size() + ptrSize) * sizeof(char)];
		memcpy(buffer, ptr, ptrSize * sizeof(char));
		buffer += ptrSize;
		memcpy(buffer, str.m_Ptr, str.size() * sizeof(char));
		return String(buffer);
	}

	int String::CalcSize(const char* ptr)
	{
		int size = 0;
		while (ptr[size] != '\0')
		{
			size++;
		}
		return size;
	}

	bool String::CompareElements(const char* ptr0, const char* ptr1, int size)
	{
		for (int i = 0; i < size; i++)
		{
			if (ptr0[i] != ptr1[i])
			{
				return false;
			}
		}
		return true;
	}

}

#endif