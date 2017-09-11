#include "Engine.h"

namespace Ablaze
{

	bool Engine::Initialise()
	{
		GLenum glewResult = glewInit();
		if (glewResult != GLEW_OK)
		{
			AB_FATAL("Failed to initialise GLEW");
			return false;
		}
		return true;
	}

	bool Engine::Shutdown()
	{
		glfwTerminate();
		return true;
	}

	String Engine::ToString() const
	{
		return "Engine";
	}

}