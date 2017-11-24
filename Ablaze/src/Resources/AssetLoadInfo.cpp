#include "AssetLoadInfo.h"

namespace Ablaze
{

	AssetLoadInfo::AssetLoadInfo() : Object(),
		m_IdCount(0)
	{

	}

	const AssetType AssetLoadInfo::Type() const
	{
		return m_AssetType;
	}

	AssetType& AssetLoadInfo::Type()
	{
		return m_AssetType;
	}

	const LoadType AssetLoadInfo::LoadMethod() const
	{
		return m_LoadType;
	}

	LoadType& AssetLoadInfo::LoadMethod()
	{
		return m_LoadType;
	}

	const std::unordered_map<String, String>& AssetLoadInfo::Identifiers() const
	{
		return m_Identifiers;
	}

	std::unordered_map<String, String>& AssetLoadInfo::Identifiers()
	{
		return m_Identifiers;
	}

	int AssetLoadInfo::IdentifierCount() const
	{
		return m_IdCount;
	}

	void AssetLoadInfo::AddIdentifier(const String& name, const String& identifier)
	{
		m_Identifiers[name] = identifier;
		m_IdCount++;
	}

	const String& AssetLoadInfo::GetIdentifier(const String& name) const
	{
		return m_Identifiers.at(name);
	}

	String& AssetLoadInfo::GetIdentifier(const String& name)
	{
		return m_Identifiers.at(name);
	}

	const String& AssetLoadInfo::operator[](const String& name) const
	{
		return GetIdentifier(name);
	}

	String& AssetLoadInfo::operator[](const String& name)
	{
		return GetIdentifier(name);
	}

	bool AssetLoadInfo::operator==(const AssetLoadInfo& other) const
	{
		return (m_AssetType == other.m_AssetType) && (m_LoadType == other.m_LoadType) && (m_Identifiers == other.m_Identifiers);
	}

	bool AssetLoadInfo::operator!=(const AssetLoadInfo& other) const
	{
		return !(*this == other);
	}

	String AssetLoadInfo::ToString() const
	{
		return "AssetLoadInfo";
	}

	void AssetLoadInfo::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("AssetType", (int)m_AssetType);
		writer.WriteAttribute("LoadType", (int)m_LoadType);
		writer.BeginObject("Identifiers");
		for (auto& pair : Identifiers())
		{
			writer.WriteAttribute(pair.first, pair.second);
		}
		writer.EndObject();
		writer.EndObject();
	}

	AssetLoadInfo AssetLoadInfo::Deserialize(JSONnode& node)
	{
		AssetLoadInfo info;
		info.m_AssetType = (AssetType)stoi(node["AssetType"].Data());
		info.m_LoadType = (LoadType)stoi(node["LoadType"].Data());
		JSONnode& identifiers = node["Identifiers"];
		for (int i = 0; i < identifiers.ChildCount(); i++)
		{
			info.AddIdentifier(identifiers[i].Key(), identifiers[i].Data());
		}
		return info;
	}

}