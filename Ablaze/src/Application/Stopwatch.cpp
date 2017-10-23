#include "Stopwatch.h"
#include "Time.h"

namespace Ablaze
{

	std::vector<Stopwatch*> Stopwatch::s_ActiveStopwatches = std::vector<Stopwatch*>();

	Stopwatch::Stopwatch(bool start) : Object(),
		m_StartTime(Time::CurrentTime()), m_Time(0.0), m_IsRunning(start)
	{
		s_ActiveStopwatches.push_back(this);
	}

	Stopwatch::~Stopwatch()
	{
		auto it = std::find(s_ActiveStopwatches.begin(), s_ActiveStopwatches.end(), this);
		s_ActiveStopwatches.erase(it);
	}

	bool Stopwatch::IsRunning() const
	{
		return m_IsRunning;
	}

	double Stopwatch::Seconds() const
	{
		if (!m_IsRunning)
		{
			return m_Time;
		}
		else
		{
			return Time::CurrentTime() - m_StartTime;
		}
	}

	double Stopwatch::Milliseconds() const
	{
		return Seconds() * 1000;
	}

	void Stopwatch::Start()
	{
		m_IsRunning = true;
	}

	void Stopwatch::Stop()
	{
		m_IsRunning = false;
		m_Time = Time::CurrentTime() - m_StartTime;
	}

	void Stopwatch::Reset()
	{
		m_StartTime = Time::CurrentTime();
		m_Time = 0.0;
	}

	String Stopwatch::ToString() const
	{
		return "Timer"; // TODO: format time
	}

}