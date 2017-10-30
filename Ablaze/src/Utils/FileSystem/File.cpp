#include "File.h"
#include "Filesystem.h"

namespace Ablaze
{

	OpenFlags operator|(OpenFlags l, OpenFlags r)
	{
		return (OpenFlags)((int)l | (int)r);
	}

	File::File(const String& filename) : Object(),
		m_Filename(filename)
	{
	
	}

	File::File() : File("")
	{
	
	}

	const String& File::Filename() const
	{
		return m_Filename;
	}

	bool File::IsOpen() const
	{
		return m_Out.is_open() || m_In.is_open();
	}

	int File::FileSize() const
	{
		return Filesystem::FileSize(m_Filename);
	}

	void File::Open(OpenFlags flags)
	{
		if (flags == OpenFlags::None)
		{
			m_Out.open(m_Filename.c_str());
			m_In.open(m_Filename.c_str());
		}
		else
		{
			m_Out.open(m_Filename.c_str(), (std::ios::openmode)flags);
			m_In.open(m_Filename.c_str(), (std::ios::openmode)flags);
		}
	}

	void File::Open(const String& filename, OpenFlags flags)
	{
		m_Filename = filename;
		Open(flags);
	}

	void File::Close()
	{
		m_Out.close();
		m_In.close();
	}

	void File::Rename(const String& newFilename)
	{
		Filesystem::Rename(m_Filename, newFilename);
	}

	void File::Clear()
	{
		Open(OpenFlags::None);
	}

	void File::Read(char* buffer, int size)
	{
		if (IsOpen())
		{
			m_In.read(buffer, size);
		}
		else
		{
			AB_ERROR("File was not opened before reading from it. File: " + m_Filename);
		}
	}

	void File::Read(char* buffer)
	{
		Read(buffer, FileSize());
	}

	char* File::Read(int size)
	{
		char* buffer = new char[size];
		Read(buffer, size);
		return buffer;
	}

	char* File::Read()
	{
		return Read(FileSize());
	}

	void File::ReadText(String* outString)
	{
		String str((std::istreambuf_iterator<char>(m_In)), std::istreambuf_iterator<char>());
		*outString = str;
	}

	String File::ReadText()
	{
		String str;
		ReadText(&str);
		return str;
	}

	std::basic_istream<char, std::char_traits<char>>& File::ReadTextLine(String* outText)
	{
		return getline(m_In, *outText);
	}

	void File::Write(const char* buffer, int size)
	{
		m_Out.write(buffer, size);
	}

	void File::WriteText(const String& text)
	{
		Write(&text[0], text.size() * sizeof(char));
	}

	String File::ToString() const
	{
		return "File";
	}

}