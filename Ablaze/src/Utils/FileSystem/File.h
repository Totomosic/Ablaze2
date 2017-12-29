#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"
#include "Logging.h"
#include "Filepath.h"

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
		Filepath m_Path;
		std::ofstream m_Out;
		std::ifstream m_In;

	public:
		File();
		File(const Filepath& filepath);

		const String& Filename() const;
		const Filepath& Path() const;
		bool IsOpen() const;
		int FileSize() const;

		void Open(OpenFlags flags = OpenFlags::Read);
		void Close();
		void Rename(const Filepath& newFilename);
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
				AB_ERROR("File was not opened. File: " + Filename());
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
				AB_ERROR("File was not opened. File: " + Filename());
			}
			return *this;
		}

		String ToString() const override;

		friend class Filesystem;

	};

}