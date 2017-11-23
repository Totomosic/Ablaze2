#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"
#include "Logging.h"

namespace Ablaze
{

	enum class OpenFlags : int
	{
		None,
		Override = std::ios::trunc,
		Read = std::ios::app,
		Append = std::ios::app
	};

	OpenFlags operator|(OpenFlags l, OpenFlags r);

	class AB_API File : public Object
	{
	private:
		String m_Filename;
		std::ofstream m_Out;
		std::ifstream m_In;

	public:
		File();
		File(const String& filename);

		const String& Filename() const;
		bool IsOpen() const;
		int FileSize() const;

		void Open(OpenFlags flags = OpenFlags::Read);
		void Open(const String& filename, OpenFlags flags = OpenFlags::Read);
		void Close();
		void Rename(const String& newFilename);
		void Clear();

		void Read(char* buffer, int size);
		void Read(char* buffer);
		char* Read(int size);
		char* Read();
		void ReadText(String* outString);
		String ReadText();
		std::basic_istream<char, std::char_traits<char>>& ReadTextLine(String* outString);

		void Write(const char* buffer, int size);
		void WriteText(const String& text);

		template<typename T>
		File& operator>>(T& out)
		{
			if (IsOpen())
			{
				m_In >> out;
			}
			else
			{
				AB_ERROR("File was not opened. File: " + m_Filename);
			}
			return *this;
		}

		template<typename T>
		File& operator<<(const T& data)
		{
			if (IsOpen())
			{
				m_Out << data;
			}
			else
			{
				AB_ERROR("File was not opened. File: " + m_Filename);
			}
			return *this;
		}

		String ToString() const override;

		friend class Filesystem;

	};

}