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

	void Asset::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.EndObject();
	}

}