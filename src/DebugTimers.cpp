#include "DebugTimers.h"


DebugTimers::DebugTimers(void)
{
	total = 0.0;
	lastTotal = 0.0;

}


DebugTimers::~DebugTimers(void)
{

}


int DebugTimers::newTimer(std::string name) {
	DRAW_REFRESH_RATE = 1.0;  // seconds
	DebugTimer temp;
	temp.name = name;
	temp.total = 0;
	timers.push_back(temp);
	return timers.size()-1;
}


void DebugTimers::draw(int x, int y) {
	t_refresh.Calculate_Ellapsed_Time();
	double elapsed = t_refresh.TotalTime();
	if(elapsed >= DRAW_REFRESH_RATE) {
		lastTotal = 0;
		std::vector<DebugTimer>::iterator it = timers.begin();
		while(it != timers.end()) {
			lastTotal += (*it).last;
			total += (*it).total;
			++it;
		}
		t_refresh.Reset(0.0);
	}

	for(int i=0; i < timers.size(); ++i) {
		std::stringstream ss; 
		if(total == 0.0 || lastTotal == 0.0) {
			ss << "No time recorded.";
		} else {
			ss << std::fixed << std::setprecision(0) << "%" << ((timers[i].last/lastTotal)*100) << " - " << timers[i].name << "(Total:" << ((timers[i].total/total)*100) << ")";
		}		
		text.text(ss, x, y - (10*++i), 0);
	}

}
