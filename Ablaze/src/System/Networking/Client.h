#pragma once
#include "Common.h"
#include "NetworkIncludes.h"

namespace Ablaze
{
	namespace Networking
	{

		class AB_API Client : public Object
		{
		private:

		public:
			Client();

			String ToString() const override;

		};

	}
}