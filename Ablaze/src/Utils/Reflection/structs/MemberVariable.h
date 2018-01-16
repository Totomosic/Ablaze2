#pragma once
#include "Types.h"
#include "Object.h"

namespace Ablaze
{
	namespace Reflection
	{

		class DataType;

		enum class Visibility
		{
			Public,
			Private,
			Protected
		};

		enum class VariableType
		{
			Value,
			ConstValue,
			MutableValue,
			Pointer,
			ConstPointer,
			MutablePointer,
			Reference,
			ConstReference
		};

		struct AB_API MemberVariable
		{
		public:
			String Name;
			Visibility Visibility;
			VariableType Attributes;
			DataType* Type;
			uint32_t Offset;

		};

	}
}