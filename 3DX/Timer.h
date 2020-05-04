#pragma once
#include <Windows.h>
class Timer
{
public:
	Timer() = default;
	bool StartTimer();
	void StopTimer();
	float GetTime() const;
	
private:
	__int64 frequency;
	__int64 startTime;
	float tickPerMs;
	float frameTime;

};