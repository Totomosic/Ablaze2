#pragma once
#include "Common.h"

namespace Ablaze
{

	enum class GraphicsAPI
	{
		OpenGL, DirectX, Vulkan
	};

	enum class DepthFunction : GLenum
	{
		Less = GL_LESS,
		Lequal = GL_LEQUAL,
		Equal = GL_EQUAL,
		Gequal = GL_GEQUAL,
		Greater = GL_GREATER
	};

	enum class BlendSrc : GLenum
	{
		SrcAlpha = GL_SRC_ALPHA,
		One = GL_ONE
	};

	enum class BlendDst : GLenum
	{
		OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
		One = GL_ONE
	};

}