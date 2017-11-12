#pragma once
#include "Common.h"

namespace Ablaze
{

	enum class AssetType
	{
		Loaded,
		Generated
	};

	class AB_API Asset : public Object
	{
	protected:
		String m_Filename;
		int m_ResourceID;
		AssetType m_AssetType;

	public:
		Asset(const String& filename);
		Asset();
		virtual ~Asset();

		virtual const String& Filename() const;
		virtual AssetType GetAssetType() const;
		virtual int ResourceID() const;

		virtual void SetFilename(const String& filename);
		virtual void SetAssetType(AssetType type);
		virtual void SetResourceID(int id);

		virtual void Reload() = 0;

		friend class ResourceManager;

	};

}