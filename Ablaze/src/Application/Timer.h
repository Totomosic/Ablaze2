#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API Timer : public Object
	{
	private:
		std::vector<Timer*> s_ActiveTimers;

	private:
		double m_CurrentTime;
		double m_TotalTime;
		bool m_Paused;

		std::function<void()> m_Callback;
		bool m_UseCallback;

	public:
		Timer(double totalTimeSeconds);
		Timer(double totalTimeSeconds, const std::function<void()>& callback);

		double CurrentTime() const;
		double TotalTime() const;
		bool IsPaused() const;
		double GetProportion() const;
		const std::function<void()>& GetCallback() const;
		bool IsUsingCallback() const;

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