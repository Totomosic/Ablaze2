#pragma once
#include "Common.h"
#include "Instructions.h"

namespace Ablaze
{
	namespace VM
	{

		union ValueData
		{
			int i32;
			float flt;
			char chr;
		};

		struct AB_API VMvalue
		{
		public:
			VMtype type;
			ValueData value;
		};

	}
}