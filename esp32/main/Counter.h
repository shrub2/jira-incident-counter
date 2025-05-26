#pragma once

#include <string>
#include <ctime>

class Counter {
public:
	Counter(int initial = 0);
	void increment();
	void reset();
	int get() const;
	void draw();
private:
	int counter;
	time_t incident_ts;
};
