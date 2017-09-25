#include "Timer.h"

namespace Ablaze
{

	std::vector<Timer*> Timer::s_ActiveTimers = std::vector<Timer*>();

	Timer::Timer(double seconds, TimerMode mode) : Object(),
		m_CurrentTime(0), m_TotalTime(seconds), m_Paused(false), m_IsTriggered(false), m_Mode(mode), m_UseCallback(false)
	{
		s_ActiveTimers.push_back(this);
	}

	Timer::Timer(double seconds, const std::function<void()>& callback, TimerMode mode) : Object(),
		m_CurrentTime(0), m_TotalTime(seconds), m_Paused(false), m_IsTriggered(false), m_Mode(mode), m_Callback(callback), m_UseCallback(true)
	{
		s_ActiveTimers.push_back(this);
	}

	Timer::~Timer()
	{
		auto it = std::find(s_ActiveTimers.begin(), s_ActiveTimers.end(), this);
		s_ActiveTimers.erase(it);
	}

	double Timer::CurrentTime() const
	{
		return m_CurrentTime;
	}

	double Timer::TotalTime() const
	{
		return m_TotalTime;
	}

	bool Timer::IsPaused() const
	{
		return m_Paused;
	}

	double Timer::GetProportion() const
	{
		return CurrentTime() / TotalTime();
	}

	const std::function<void()>& Timer::GetCallback() const
	{
		return m_Callback;
	}

	bool Timer::IsUsingCallback() const
	{
		return m_UseCallback;
	}

	bool Timer::IsTriggered() const
	{
		return m_IsTriggered;
	}

	void Timer::SetCallback(const std::function<void()>& callback)
	{
		m_Callback = callback;
		m_UseCallback = true;
	}

	void Timer::DisableCallback()
	{
		m_UseCallback = false;
	}

	void Timer::SetCurrentTime(double seconds)
	{
		m_CurrentTime = seconds;
	}

	void Timer::SetTotalTime(double seconds)
	{
		m_TotalTime = seconds;
	}

	void Timer::Start()
	{
		m_Paused = false;
	}

	void Timer::Stop()
	{
		m_Paused = true;
	}

	void Timer::Reset()
	{
		m_CurrentTime = 0;
	}

	void Timer::Trigger()
	{
		if (m_UseCallback)
		{
			m_Callback();
		}
	}

	String Timer::ToString() const
	{
		// TODO: format time string
		return "";
	}

	void Timer::Update(double elapsedSeconds)
	{
		m_IsTriggered = false;
		m_CurrentTime += elapsedSeconds;
		if (m_CurrentTime >= m_TotalTime)
		{
			Trigger();
			m_CurrentTime -= m_TotalTime;
			m_IsTriggered = true;
			if (m_Mode == TimerMode::Single)
			{
				Stop();
				Reset();
			}
		}
	}

}