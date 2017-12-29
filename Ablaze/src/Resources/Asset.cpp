#include "Asset.h"

namespace Ablaze
{

	Asset::Asset() : Object(),
		m_RefCount(0)
	{
		
	}

	Asset::~Asset()
	{

	}

	int Asset::GetRefCount() const
	{
		return m_RefCount;
	}

	void Asset::Increment()
	{
		m_RefCount++;
	}

	void Asset::Decrement(bool deleteIfZero)
	{
		m_RefCount--;
		if (deleteIfZero && (m_RefCount <= 0))
		{
			delete this;
		}
	}

	void Asset::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.EndObject();
	}

}