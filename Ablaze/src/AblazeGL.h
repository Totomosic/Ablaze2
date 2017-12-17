#pragma once
#include <freetype-gl.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Object.h"
#include "Logging.h"

namespace Ablaze
{
	inline String ConvertError(GLenum error)
	{
		switch (error) {
		case 0x0500: return "GL_INVALID_ENUM";
		case 0x0501: return "GL_INVALID_VALUE";
		case 0x0502: return "GL_INVALID_OPERATION";
		case 0x0503: return "GL_STACK_OVERFLOW";
		case 0x0504: return "GL_STACK_UNDERFLOW";
		case 0x0505: return "GL_OUT_OF_MEMORY";
		case 0x0506: return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case 0x0507: return "GL_CONTEXT_LOST";
		case 0x8031: return "GL_TABLE_TOO_LARGE";
		}
		return "Unknown error";
	}

	inline bool CheckErrors(int line, const char* file)
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			AB_ERROR("OpenGL Error: " + ConvertError(error) + " (" + std::to_string(error) + ") LINE " + std::to_string(line) + " FILE: " + String(file));
			return false;
		}
		return true;
	}

#ifdef AB_DEBUG
	#define GL_CALL(func) func; AB_ASSERT(CheckErrors(__LINE__, __FILE__), "OPENGL ERROR")
#else
	#define GL_CALL(func) func
#endif
}