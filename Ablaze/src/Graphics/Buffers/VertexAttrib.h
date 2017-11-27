#pragma once
#include "Common.h"

namespace Ablaze
{

	struct AB_API VertexAttrib
	{
	public:
		uint index;
		int count;
		GLenum dataType;
		bool normalized;
		int offset;

	public:
		VertexAttrib(uint index, int count, GLenum dataType, bool normalized, int offset);
		VertexAttrib();

	};

}