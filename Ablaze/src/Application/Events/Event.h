#pragma once
#include "Common.h"
#include "EventArgs.h"

namespace Ablaze
{

	typedef std::function<void(const EventArgs* const)> EventCallback;

	class AB_API Event : public Object
	{
	private:
		std::vector<EventCallback> m_Subscribers;

	public:
		Event();
		
		int SubscribedCount() const;

		void Subscribe(const EventCallback& method);
		void Unsubscribe(const EventCallback& method);

		void Trigger(const EventArgs* const args) const;
		void operator()(const EventArgs* const args) const;

	};

}