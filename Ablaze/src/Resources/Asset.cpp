#include "Asset.h"

namespace Ablaze
{

	Asset::Asset() : Object()
	{
		
	}

	const int Asset::AssetID() const
	{
		return m_AssetID;
	}

	int& Asset::AssetID()
	{
		return m_AssetID;
	}

	const AssetLoadInfo& Asset::Info() const
	{
		return m_LoadInfo;
	}

	AssetLoadInfo& Asset::Info()
	{
		return m_LoadInfo;
	}

	void Asset::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteObject("Info", m_LoadInfo);
		writer.EndObject();
	}

}