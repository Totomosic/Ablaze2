#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API GraphicsPipeline : public Object
	{
	private:

	public:
		GraphicsPipeline();
		~GraphicsPipeline();

		String ToString() const override;

	};

}