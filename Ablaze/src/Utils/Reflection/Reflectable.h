#pragma once
#include "Types.h"
#include "Object.h"

#include "structs\__structs__.h"

namespace Ablaze
{
	namespace Reflectable
	{

		template<typename T>
		class AB_API Reflectable : public Object
		{
		private:
			DataType* m_DataType;

		public:
			const DataType& Type() const
			{
				return *m_DataType;
			}

		};

	}
}