#pragma once
#include "Common.h"
#include "AssetLoadInfo.h"

namespace Ablaze
{

	class AB_API Asset : public Object
	{
	protected:
		AssetLoadInfo m_LoadInfo;
		int m_AssetID;

	public:
		Asset();

		const int AssetID() const;
		int& AssetID();
		const AssetLoadInfo& Info() const;
		AssetLoadInfo& Info();

		virtual void Reload() = 0;
		virtual void Serialize(JSONwriter& writer) const;

		friend class ResourceManager;

	};

}