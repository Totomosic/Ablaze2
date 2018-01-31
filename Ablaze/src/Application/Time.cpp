#include "Time.h"

namespace Ablaze
{
	
	double Time::s_TotalSeconds = 0.0;
	double Time::s_LastSeconds = 0.0;
	double Time::s_TotalRealSeconds = 0.0;
	double Time::s_LastRealSeconds = 0.0;
	double Time::s_ElapsedSeconds = 0.0;
	double Time::s_TimeScale = 1.0;

	std::vector<double> Time::s_Frames;
	double Time::s_AvgFps = 60.0;
	double Time::s_AvgTimer = 0.0;

	std::vector<Timer*> Time::s_ActiveTimers = std::vector<Timer*>();

	double Time::DeltaTime()
	{
		return s_ElapsedSeconds;
	}

	double Time::ElapsedTime()
	{
		return DeltaTime();
	}

	double Time::CurrentTime()
	{
		s_TotalRealSeconds = glfwGetTime();
		double realElapsed = s_TotalRealSeconds - s_LastRealSeconds;
		double scaledElapsed = realElapsed * TimeScale();
		s_TotalSeconds += scaledElapsed;
		s_LastRealSeconds = s_TotalRealSeconds;
		return s_TotalSeconds;
	}

	double& Time::TimeScale()
	{
		return s_TimeScale;
	}

	double Time::FramesPerSecond()
	{
		return 1.0 / ElapsedTime();
	}

	double Time::AvgFPS()
	{
		return s_AvgFps;
	}

	void Time::Reset()
	{
		glfwSetTime(0.0);
		s_TotalSeconds = 0;
		s_TotalRealSeconds = 0;
		s_LastSeconds = 0;
		s_LastRealSeconds = 0;
		s_ElapsedSeconds = 0;
		s_AvgTimer = 0;
		s_AvgFps = 60;
		s_Frames.clear();
	}

	Stopwatch& Time::CreateNewStopwatch(bool start)
	{
		return *(new Stopwatch(start));
	}

	Timer& Time::CreateNewTimer(double seconds, TimerMode mode)
	{
		Timer* t = new Timer(seconds, mode);
		s_ActiveTimers.push_back(t);
		return *t;
	}

	Timer& Time::CreateNewTimer(double seconds, const std::function<void()>& callback, TimerMode mode)
	{
		Timer* t = new Timer(seconds, callback, mode);
		s_ActiveTimers.push_back(t);
		return *t;
	}

	void Time::Update()
	{
		s_TotalSeconds = CurrentTime();
		s_ElapsedSeconds = s_TotalSeconds - s_LastSeconds;
		s_LastSeconds = CurrentTime();

		s_Frames.push_back(FramesPerSecond());
		s_AvgTimer += s_ElapsedSeconds;
		if (s_AvgTimer > 0.5)
		{
			CalcAvgFPS();
		}

		for (int i = 0; i < s_ActiveTimers.size(); i++)
		{
			s_ActiveTimers[i]->Update(s_ElapsedSeconds);
		}
	}

	void Time::CalcAvgFPS()
	{
		double total = 0;
		for (auto val : s_Frames)
		{
			total += val;
		}
		total /= s_Frames.size();
		s_Frames.clear();
		s_AvgTimer = 0;
		s_AvgFps = total;
	}

}