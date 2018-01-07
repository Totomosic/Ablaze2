#include "JSONwriter.h"
#include "Utils\Filesystem\__Filesystem__.h"

namespace Ablaze
{

	JSONwriter::JSONwriter(const String& jsonFile) : Object(),
		m_Filename(jsonFile)
	{
		if (jsonFile.find('/') != String::npos)
		{
			size_t slash = jsonFile.find_last_of('/');
			String dir = jsonFile.substr(0, slash + 1);
			Filesystem::CreateNewDirectory(dir);
		}
		m_File = Filesystem::OpenFile(jsonFile, OpenFlags::Override);
		m_File.Clear();
		m_File.Close();
		m_File.Open(OpenFlags::Append);
	}

	JSONwriter::~JSONwriter()
	{
		RemoveTrailingComma();
		m_File.Close();
	}

	const String& JSONwriter::Filename() const
	{
		return m_Filename;
	}

	void JSONwriter::BeginObject(const String& attributeTag)
	{
		WriteAttribute(attributeTag);
		m_File << '{';
	}

	void JSONwriter::BeginObject()
	{
		m_File << '{';
	}

	void JSONwriter::EndObject()
	{
		RemoveTrailingComma();
		m_File << '}';
		WriteComma();
	}

	void JSONwriter::BeginArray(const String& attributeTag)
	{
		WriteAttribute(attributeTag);
		m_File << '[';
	}

	void JSONwriter::EndArray()
	{
		RemoveTrailingComma();
		m_File << ']';
		WriteComma();
	}

	String JSONwriter::ToString() const
	{
		return "JSONwriter";
	}

	void JSONwriter::WriteAttribute(const String& attributeTag)
	{
		m_File << '\"' << attributeTag << "\" : ";
	}

	void JSONwriter::WriteComma()
	{
		m_File << ", ";
	}

	void JSONwriter::RemoveTrailingComma()
	{
		m_File.Close();
		m_File.Open(OpenFlags::Read);
		String data = m_File.ReadText();
		m_File.Close();
		if (data[data.length() - 2] == ',')
		{
			m_File.Open(OpenFlags::Override);
			m_File.WriteText(data.substr(0, data.length() - 2));
			m_File.Close();
		}		
		m_File.Open(OpenFlags::Append);
	}

}