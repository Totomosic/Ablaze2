#pragma once
#include "Common.h"
#include "Graphics\Buffers\__Buffers__.h"

namespace Ablaze
{

	struct AB_API ModelInfo
	{
	public:
		VertexArray* Array;
		VertexBuffer* Buffer;
		IndexBuffer* Indices;
		int64 VertexCount;
		int64 RenderCount;

		const void* Vertices;

	};

}