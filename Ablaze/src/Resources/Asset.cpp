#include "Asset.h"

namespace Ablaze
{

	Asset::Asset(const String& filename) : Object(),
		m_Filename(filename), m_IsFromFile(true)
	{
	
	}

	Asset::Asset() : Object(),
		m_Filename(""), m_IsFromFile(false)
	{
	
	}

	Asset::~Asset()
	{
		
	}

	const String& Asset::GetFilename() const
	{
		return m_Filename;
	}

	bool Asset::IsFromFile() const
	{
		return m_IsFromFile;
	}

	void Asset::SetFilename(const String& filename)
	{
		m_Filename = filename;
		if (filename != "")
		{
			SetIsFromFile(true);
		}
		else
		{
			SetIsFromFile(false);
		}
	}

	void Asset::SetIsFromFile(bool isFromFile)
	{
		m_IsFromFile = isFromFile;
	}

}