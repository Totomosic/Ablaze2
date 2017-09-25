#pragma once
#include "Types.h"

#define USE_ABLAZE_STRING 0

#if !USE_ABLAZE_STRING

typedef std::string String;

#else

namespace Ablaze
{

	class AB_API String
	{
	private:
		const char* m_Ptr;
		int m_Size;

	public:
		String();
		String(const char* str);
		String(const String& other);
		String(const std::string& other);
		~String();

		int size() const;
		int length() const;
		const char* c_str() const;
		bool empty() const;

		char operator[](int index) const;
		String operator+(const String& other) const;
		String operator+(const char* other) const;
		bool operator==(const String& other) const;
		bool operator!=(const String& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const String& string);
		friend String operator+(const char* ptr, const String& str);

	private:
		static int CalcSize(const char* ptr);
		static bool CompareElements(const char* ptr0, const char* ptr1, int size);

	};

}

namespace std
{

	template<>
	struct hash<Ablaze::String>
	{
		size_t operator()(const Ablaze::String& string) const
		{
			return 0;
		}
	};

}
#endif