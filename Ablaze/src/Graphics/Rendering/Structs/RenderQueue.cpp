#include "RenderQueue.h"

namespace Ablaze
{

	RenderQueue::RenderQueue() : Object()
	{
	
	}

	void RenderQueue::Enqueue(GameObject* object)
	{
		m_Queue.push_back(object);
	}

	GameObject* RenderQueue::Next()
	{
		GameObject* obj = m_Queue.front();
		m_Queue.pop_front();
		return obj;
	}

	void RenderQueue::Clear()
	{
		m_Queue.clear();
	}

	String RenderQueue::ToString() const
	{
		return "RenderQueue";
	}

}