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
		for (int i = 0; i < m_Commands.size(); i++)
		{
			ExecuteNext(renderer);
		}
	}

	String CommandQueue::ToString() const
	{
		return "CommandQueue";
	}

}