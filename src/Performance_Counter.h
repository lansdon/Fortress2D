#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <Windows.h>

class Performance_Counter
{
private:
	LARGE_INTEGER CurrentTickCount_;
	LARGE_INTEGER OldTickCount_;
	LARGE_INTEGER TickFrquency_;
	double EllapsedTime_;
	double TotalTime_;
public:
	Performance_Counter();

	void Reset(const double intial_time);
	
	void Calculate_Ellapsed_Time();
	
	void Calculate_Ellapsed_Time(const Performance_Counter& to_intialize);
	
	const LARGE_INTEGER& Current_Tick_Count() const;

	
	double Ellapsed_Milliseconds() const;
	double Ellapsed_Seconds() const;
	double TotalTime() const;
};

#endif