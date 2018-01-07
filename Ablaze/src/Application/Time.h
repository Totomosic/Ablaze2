#pragma once
#include "Common.h"
#include "Timer.h"
#include "Stopwatch.h"

namespace Ablaze
{

	class AB_API Time
	{
	private:
		static double s_TotalSeconds;
		static double s_LastSeconds;
		static double s_TotalRealSeconds;
		static double s_LastRealSeconds;

		static double s_ElapsedSeconds;
		static double s_TimeScale;

		static std::vector<double> s_Frames;
		static double s_AvgFps;
		static double s_AvgTimer;

		static std::vector<Timer*> s_ActiveTimers;

	public:
		Time() = delete;

	public:
		static double ElapsedTime();
		static double DeltaTime();
		static double CurrentTime();
		static double& TimeScale();

		static double FramesPerSecond();
		static double AvgFPS();

		static void Reset();

		static Stopwatch& CreateNewStopwatch(bool start = false);

		static Timer& CreateNewTimer(double seconds, TimerMode mode = TimerMode::Repeat);
		static Timer& CreateNewTimer(double seconds, const std::function<void()>& callback, TimerMode mode = TimerMode::Repeat);

		template<class C, void(C::*M)()>
		static Timer& CreateNewTimer(double seconds, C* const instance)
		{
			return CreateNewTimer(seconds, std::bind(M, instance));
		}

		friend class Application;

	private:
		static void Update();
		static void CalcAvgFPS();

	};

}