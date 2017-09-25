#pragma once
#include "Common.h"

namespace Ablaze
{

	enum class TimerMode
	{
		Single,
		Repeat
	};

	class AB_API Timer : public Object
	{
	private:
		static std::vector<Timer*> s_ActiveTimers;

	private:
		double m_CurrentTime;
		double m_TotalTime;
		bool m_Paused;
		bool m_IsTriggered;
		TimerMode m_Mode;

		std::function<void()> m_Callback;
		bool m_UseCallback;

	public:
		Timer(double totalTimeSeconds, TimerMode mode = TimerMode::Repeat);
		Timer(double totalTimeSeconds, const std::function<void()>& callback, TimerMode mode = TimerMode::Repeat);
		~Timer();

		double CurrentTime() const;
		double TotalTime() const;
		bool IsPaused() const;
		double GetProportion() const;
		const std::function<void()>& GetCallback() const;
		bool IsUsingCallback() const;
		bool IsTriggered() const;

		void SetCallback(const std::function<void()>& callback);
		void DisableCallback();
		void SetCurrentTime(double time);
		void SetTotalTime(double time);

		void Start();
		void Stop();
		void Reset();
		void Trigger();

		String ToString() const override;

		friend class Time;

	private:
		void Update(double elapsedSeconds);

	};

}