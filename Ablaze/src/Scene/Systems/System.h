#pragma once
#include "Common.h"
#include "Scene\GameObject.h"
#include "Scene\Components\__Components__.h"
#include "Application\Timer.h"
#include "Application\Input\Input.h"
#include "Application\Time.h"

namespace Ablaze
{

	class AB_API System : public Object
	{
	public:
		virtual void Execute() = 0;
		void operator()()
		{
			Execute();
		}

		String ToString() const override
		{
			return "System";
		}

	};

}