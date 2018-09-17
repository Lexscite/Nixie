#include "../stdafx.h"

#include "time.h"

namespace nixie
{
	Time* Time::singleton_;

	Time* Time::Get()
	{
		if (singleton_ == nullptr)
			singleton_ = new Time;

		return singleton_;
	}

	Time::Time() :
		seconds_per_count_(0),
		delta_time_(-1),
		base_time_(0),
		paused_time_(0),
		previous_time_(0),
		current_time_(0),
		is_stopped_(false)
	{
		__int64 counts_per_second;
		QueryPerformanceFrequency((LARGE_INTEGER*)&counts_per_second);
		seconds_per_count_ = 1 / (double)counts_per_second;
	}

	void Time::Start()
	{
		__int64 start_time;
		QueryPerformanceCounter((LARGE_INTEGER*)&start_time);

		if (is_stopped_)
		{
			paused_time_ += (start_time - stop_time_);
			previous_time_ = start_time;
			stop_time_ = 0;
			is_stopped_ = false;
		}
	}

	void Time::Stop()
	{
		if (!is_stopped_)
		{
			__int64 current_time;
			QueryPerformanceCounter((LARGE_INTEGER*)&current_time);

			stop_time_ = current_time;
			is_stopped_ = true;
		}
	}

	void Time::Reset()
	{
		__int64 current_time;
		QueryPerformanceCounter((LARGE_INTEGER*)&current_time);

		base_time_ = current_time;
		previous_time_ = current_time;
		stop_time_ = 0;
		is_stopped_ = false;
	}

	void Time::Tick()
	{
		if (is_stopped_)
		{
			delta_time_ = 0;
			return;
		}

		__int64 current_time;
		QueryPerformanceCounter((LARGE_INTEGER*)&current_time);
		current_time_ = current_time;

		delta_time_ = (current_time_ - previous_time_) * seconds_per_count_;

		previous_time_ = current_time_;

		if (delta_time_ < 0)
			delta_time_ = 0;
	}

	float Time::GetDeltaTime()
	{
		return static_cast<float>(Time::Get()->delta_time_);
	}

	float Time::GetTime() const
	{
		if (is_stopped_)
			return static_cast<float>(((stop_time_ - paused_time_) - base_time_) * seconds_per_count_);
		else
			return static_cast<float>(((current_time_ - paused_time_) - base_time_) * seconds_per_count_);
	}
}