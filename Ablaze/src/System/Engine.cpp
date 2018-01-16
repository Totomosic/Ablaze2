#include "Engine.h"
#include "Application\Input\Input.h"
#include "Graphics\Rendering\Graphics.h"
#include "BytecodeVM\__BytecodeVM__.h"
#include "Scene\Systems\Systems.h"
#include "Resources\ResourceManager.h"

#include "Networking\NetworkIncludes.h"

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
		Filesystem::Initialise();
		Random::Initialise();
		Input::Initialise();
		Shader::Initialise();
		VM::VirtualMachine::Initialise();
		Systems::Initialise();
		return true;
	}

	bool Engine::Shutdown()
	{
		ResourceManager::Terminate();
		Graphics::Terminate();
		WSACleanup();
		glfwTerminate();
		return true;
	}

	String Engine::ToString() const
	{
		return "Engine";
	}

}