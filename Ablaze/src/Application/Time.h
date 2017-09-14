#pragma once
#include "Common.h"
#include "Timer.h"

namespace Ablaze
{

	class AB_API Time : public Object
	{
	private:
		static double s_TotalSeconds;
		static double s_LastSeconds;
		static double s_ElapsedSeconds;

		static std::vector<double> s_Frames;
		static double s_AvgFps;
		static double s_AvgTimer;

	public:
		Time() = delete;
		String ToString() const override;

	public:
		static double TotalTime();
		static double ElapsedTime();
		static double DeltaTime();

		static double FramesPerSecond();
		static double AvgFPS();

		static void Reset();

		static Timer* CreateNewTimer(double seconds);
		static Timer* CreateNewTimer(double seconds, const std::function<void()>& callback);

		friend class Application;

	private:
		static void Update();
		static void CalcAvgFPS();

	};

}