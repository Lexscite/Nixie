#ifndef TIME_H
#define TIME_H

#include <windows.h>

#pragma once

class Time
{
public:
	Time();

	void Start();
	void Stop();
	void Reset();
	void Tick();

	float GetTime() const;
	float GetDeltaTime() const;

private:
	double seconds_per_count_;
	double delta_time_;

	__int64 base_time_;
	__int64 paused_time_;
	__int64 stop_time_;
	__int64 previous_time_;
	__int64 current_time_;

	bool is_stopped_;
};

#endif