#pragma once
#include "Object.h"
#include "MemberMethod.h"
#include "MemberVariable.h"

namespace Ablaze
{
	namespace Reflection
	{

		class AB_API DataType
		{
		private:
			String m_Name;
			DataType* m_BaseType;
			uint32_t m_Size;
			std::vector<MemberVariable> m_MemberVariables;
			std::vector<MemberMethod> m_MemberMethods;

		public:
			DataType();

			const String& Name() const;
			const DataType& Base() const;
			bool HasBase() const;
			uint32_t Size() const;
			const std::vector<MemberVariable>& MemberVariables() const;
			const std::vector<MemberMethod>& MemberMethods() const;

		};

	}
}