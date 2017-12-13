#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API Asset : public Object
	{
	protected:
		int m_AssetID;

	public:
		Asset();

		const int AssetID() const;
		int& AssetID();

		virtual void Reload() = 0;
		virtual void Serialize(JSONwriter& writer) const;

		friend class ResourceManager;

	};

}