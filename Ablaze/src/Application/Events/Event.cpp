#include "Event.h"

namespace Ablaze
{

	Event::Event() : Object()
	{
		
	}

	int Event::SubscribedCount() const
	{
		return m_Subscribers.size();
	}

	void Event::Subscribe(const EventCallback& callback)
	{
		m_Subscribers.push_back(callback);
	}

	void Event::Unsubscribe(const EventCallback& callback)
	{
		
	}

	void Event::Trigger(const EventArgs* const args) const
	{
		for (auto callback : m_Subscribers)
		{
			callback(args);
		}
	}
	
	void Event::operator()(const EventArgs* const args) const
	{
		Trigger(args);
	}

}