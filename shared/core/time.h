#ifndef VOODOO_TIME_H_
#define VOODOO_TIME_H_

#pragma once


namespace voodoo
{
	class Time
	{
	public:
		static Time* Get();

		void Start();
		void Stop();
		void Reset();
		void Tick();

		float GetTime() const;
		static float GetDeltaTime();

	private:
		Time();

	private:
		static Time* singleton_;

		double seconds_per_count_;
		double delta_time_;

		__int64 base_time_;
		__int64 paused_time_;
		__int64 stop_time_;
		__int64 previous_time_;
		__int64 current_time_;

		bool is_stopped_;
	};
}

#endif