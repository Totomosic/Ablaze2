#include "VertexAttrib.h"

namespace Ablaze
{

	VertexAttrib::VertexAttrib(uint index, int count, GLenum dataType, bool normalized, int offset) : Object(),
		index(index), count(count), dataType(dataType), normalized(normalized), offset(offset)
	{
		
	}

	VertexAttrib::VertexAttrib() : VertexAttrib(0, 1, GL_FLOAT, false, 0)
	{
	
	}

	String VertexAttrib::ToString() const
	{
		return "Vertex Attribute";
	}

}