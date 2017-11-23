#pragma once
#include "JSONwriter.h"

namespace Ablaze
{

	class AB_API ISerializable
	{
	public:
		virtual void Serialize(JSONwriter& writer) const = 0;

	};

}