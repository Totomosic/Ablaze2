#pragma once
#include "Common.h"

namespace Ablaze
{

	// Class that acts as a smart pointer for resources in Ablaze - non-polymorphic
	template<typename T>
	class AB_API Resource : public Object
	{
	private:
		T* m_ResourcePtr;

	private:
		Resource(T* resource) { m_ResourcePtr = resource; }

	public:
		T* Get() const { return m_ResourcePtr; }
		T* operator*() const { return Get(); }

		String ToString() const override
		{
			return "Resource";
		}

	};

}