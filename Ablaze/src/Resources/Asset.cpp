#include "Asset.h"

namespace Ablaze
{

	Asset::Asset(const String& filename) : Object(),
		m_Filename(filename), m_AssetType(AssetType::Loaded), m_ResourceID(-1)
	{
	
	}

	Asset::Asset() : Object(),
		m_Filename(""), m_AssetType(AssetType::Generated), m_ResourceID(-1)
	{
	
	}

	Asset::~Asset()
	{
		
	}

	const String& Asset::Filename() const
	{
		return m_Filename;
	}

	AssetType Asset::GetAssetType() const
	{
		return m_AssetType;
	}

	int Asset::ResourceID() const
	{
		return m_ResourceID;
	}

	void Asset::SetFilename(const String& filename)
	{
		m_Filename = filename;
	}

	void Asset::SetAssetType(AssetType type)
	{
		m_AssetType = type;
	}

	void Asset::SetResourceID(int id)
	{
		m_ResourceID = id;
	}

}