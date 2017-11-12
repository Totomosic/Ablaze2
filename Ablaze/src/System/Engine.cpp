#include "Engine.h"
#include "Application\Input\Input.h"
#include "Graphics\Graphics.h"
#include "BytecodeVM\__BytecodeVM__.h"
#include "Scene\Systems\Systems.h"

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
		Random::Initialise();
		Input::Initialise();
		VM::VirtualMachine::Initialise();
		Systems::Initialise();
		return true;
	}

	bool Engine::Shutdown()
	{
		Graphics::Terminate();
		glfwTerminate();
		return true;
	}

	String Engine::ToString() const
	{
		return "Engine";
	}

}