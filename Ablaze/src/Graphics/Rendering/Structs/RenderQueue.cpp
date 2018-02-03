#include "RenderQueue.h"
#include "Scene\Components\__Components__.h"

namespace Ablaze
{

	RenderQueue::RenderQueue(RenderOrder order) : Object(),
		m_Order(order)
	{
	
	}

	int RenderQueue::Size() const
	{
		return m_Queue.size();
	}

	void RenderQueue::Enqueue(GameObject* object)
	{
		m_Queue.push_back(object);
	}

	void RenderQueue::Sort()
	{
		if (m_Order == RenderOrder::FrontToBack)
		{
			std::sort(m_Queue.begin(), m_Queue.end(), RenderQueue::FToBSort);
		}
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

	bool RenderQueue::FToBSort(GameObject* left, GameObject* right)
	{
		return (Maths::Vector3f::Distance(left->transform().Position(), left->GetLayer()->GetActiveCamera().transform().Position()) < Maths::Vector3f::Distance(right->transform().Position(), right->GetLayer()->GetActiveCamera().transform().Position()));
	}

}