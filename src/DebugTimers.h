#pragma once

#include <vector>
#include "Performance_Counter.h"
#include <string>
#include "GLText.h"
#include <iomanip>
#include <sstream>


class DebugTimers
{
public:
	DebugTimers(void);
	~DebugTimers(void);

	GLText text;

	struct DebugTimer {
		DebugTimer() { name="DebugTimer"; total=0.0; }
		std::string name;
		Performance_Counter timer;
		double total, last, lastDisplay, totalDisplay;
		void start() { timer.Reset(0);};
		void stop() { timer.Calculate_Ellapsed_Time(); last += timer.TotalTime(); total += timer.TotalTime(); }
		void resetLast() { last = 0.0; }
	};

	int newTimer(std::string name);					// Get timer ID 
	void draw(int x=600, int y=450);									// Draw
	void start(int id) { timers[id].start(); }		// Use at beginning of code to be timed w/ specific timer ID
	void stop(int id) { timers[id].stop(); }		// Use at the end of code being timed using specific timer ID

	std::vector<DebugTimer> timers;

	long double total, lastTotal, displayTotal;

	// Refresh timer
	float DRAW_REFRESH_RATE;
	Performance_Counter t_refresh;
};

