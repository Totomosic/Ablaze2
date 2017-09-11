#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API Engine : public Object
	{
	private:

	public:
		Engine() = delete;

		static bool Initialise();
		static bool Shutdown();

		String ToString() const override;

	};

}