#pragma once
#include "Types.h"

namespace Ablaze
{

	class AB_API Object
	{
	public:
		virtual String ToString() const = 0;

	};

	class AB_API GLObject : public Object
	{
	protected:
		uint m_Id;

	public:
		virtual ~GLObject() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint GetID() const { return m_Id; }

	};

}