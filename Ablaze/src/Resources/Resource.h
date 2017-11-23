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

	public:
		Resource(T* resource)
		{
			m_ResourcePtr = resource;
		}

		Resource() = default;

		Resource(const Resource<T>& other)
		{
			m_ResourcePtr = other.m_ResourcePtr;
			if (other.m_ResourcePtr != nullptr)
				ResourceManager::Library().IncrementRefCount(m_ResourcePtr->Info());
		}

		template<typename Other>
		Resource(const Resource<Other>& other)
		{
			m_ResourcePtr = (T*)other.m_ResourcePtr;
			if (other.m_ResourcePtr != nullptr)
				ResourceManager::Library().IncrementRefCount(m_ResourcePtr->Info());
		}

		~Resource()
		{
			if (m_ResourcePtr != nullptr)
				ResourceManager::Library().DecrementRefCount(m_ResourcePtr->Info());
		}

		T* Get() const { return m_ResourcePtr; }
		T* operator*() const { return Get(); }
		T* operator->() const { return Get(); }

		void Increment() const
		{
			ResourceManager::Library().IncrementRefCount(m_ResourcePtr->Info());
		}

		template<typename> friend class Resource;

		String ToString() const override
		{
			return m_ResourcePtr->ToString();
		}

		void Serialize(JSONwriter& writer) const
		{
			m_ResourcePtr->Serialize(writer);
		}

	};

}