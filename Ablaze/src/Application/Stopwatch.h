#pragma once
#include "Common.h"

namespace Ablaze
{

	class Stopwatch : public Object
	{
	private:
		static std::vector<Stopwatch*> s_ActiveStopwatches;

	private:
		double m_StartTime;
		double m_Time;
		bool m_IsRunning;

	public:
		Stopwatch(bool start = false);
		Stopwatch(const Stopwatch& other) = delete;
		~Stopwatch();

		bool IsRunning() const;
		double Seconds() const;
		double Milliseconds() const;

		void Start();
		void Stop();
		void Reset();

		String ToString() const override;

		friend class Time;
		
	};

}