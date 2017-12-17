#include "CommandQueue.h"
#include "RenderCommand.h"
#include "Graphics\Rendering\Structs\Renderer.h"

namespace Ablaze
{

	CommandQueue::CommandQueue() : Object()
	{
	
	}

	CommandQueue::~CommandQueue()
	{
		for (RenderCommand* command : m_Commands)
		{
			delete command;
		}
	}

	void CommandQueue::Enqueue(RenderCommand* command)
	{
		m_Commands.push_back(command);
	}

	void CommandQueue::ExecuteNext(Renderer& renderer)
	{
		RenderCommand* command = m_Commands.front();
		command->Execute(renderer);
		m_Commands.pop_front();
		delete command;
	}

	void CommandQueue::ExecuteAll(Renderer& renderer)
	{
		int length = m_Commands.size();
		for (int i = 0; i < length; i++)
		{
			ExecuteNext(renderer);
		}
	}

	void CommandQueue::Clear()
	{
		m_Commands.clear();
	}

	String CommandQueue::ToString() const
	{
		return "CommandQueue";
	}

}