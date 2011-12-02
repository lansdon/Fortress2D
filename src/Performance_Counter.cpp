//#include "Timer.h"
#include "Performance_Counter.h"

Performance_Counter::Performance_Counter():EllapsedTime_(0.0), TotalTime_(0.0)
{
		::QueryPerformanceFrequency(&TickFrquency_);
		::QueryPerformanceCounter(&CurrentTickCount_);
		OldTickCount_ = CurrentTickCount_;
}

void Performance_Counter::Reset(const double intial_time = 0.0)
{
		TotalTime_ = intial_time;
		EllapsedTime_ = intial_time;
		::QueryPerformanceCounter(&CurrentTickCount_);
		OldTickCount_ = CurrentTickCount_;
}

void Performance_Counter::Calculate_Ellapsed_Time()
{
		::QueryPerformanceCounter(&CurrentTickCount_);
		EllapsedTime_ = (double)(CurrentTickCount_.QuadPart - OldTickCount_.QuadPart)/TickFrquency_.QuadPart;
		TotalTime_ += EllapsedTime_;
		OldTickCount_ = CurrentTickCount_;
}

void Performance_Counter::Calculate_Ellapsed_Time(const Performance_Counter& to_intialize)
{
		CurrentTickCount_ = to_intialize.Current_Tick_Count();
		EllapsedTime_ = (double)(CurrentTickCount_.QuadPart - OldTickCount_.QuadPart)/TickFrquency_.QuadPart;
		TotalTime_ += EllapsedTime_;
		OldTickCount_ = CurrentTickCount_;
}

const LARGE_INTEGER& Performance_Counter::Current_Tick_Count() const {return CurrentTickCount_;}

double Performance_Counter::Ellapsed_Milliseconds() const {return EllapsedTime_ * 1000;}

double Performance_Counter::Ellapsed_Seconds() const {return EllapsedTime_;}

double Performance_Counter::TotalTime() const {return TotalTime_;}

