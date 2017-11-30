#pragma once
#include "Common.h"
#include "ResourceManager.h"

namespace Ablaze
{

	// Class that acts as a smart pointer for resources in Ablaze - non-polymorphic
	template<typename T>
	class AB_API Resource : public Object
	{
	private:
		T* m_ResourcePtr;
		mutable bool m_Delete;

	public:
		Resource(T* resource)
		{
			m_ResourcePtr = resource;
			m_Delete = true;
		}

		Resource() : Resource(nullptr)
		{
		
		}

		~Resource()
		{
			if (m_ResourcePtr != nullptr && m_Delete)
			{
				delete m_ResourcePtr;
			}
		}

		T* Get() const { return m_ResourcePtr; }
		T* operator*() const { return Get(); }
		T* operator->() const { return Get(); }

		template<typename> friend class Resource;

		String ToString() const override
		{
			return m_ResourcePtr->ToString();
		}

		void Serialize(JSONwriter& writer) const
		{
			if (m_ResourcePtr != nullptr)
			{
				m_ResourcePtr->Serialize(writer);
			}
		}

	};

}