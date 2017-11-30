#pragma once
#include "Common.h"
#include "Structs\__Structs__.h"

namespace Ablaze
{

	struct AB_API GraphicsPipeline
	{
	public:
		RenderSchedule* Schedule;
		Renderer* Renderer;

	};

}