#pragma once
#include "Object.h"

namespace Ablaze
{
	namespace Reflection
	{

		class DataType;

		struct AB_API MemberMethod
		{
		public:
			String Name;
			DataType* ReturnType;
			std::vector<DataType*> Arguments;

		};

	}
}