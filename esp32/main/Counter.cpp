#include <string>
#include "Counter.h"
#include "lcdgfx.h"

extern DisplaySSD1306_128x64_I2C display;

Counter::Counter(int initial) : counter(initial) {}

void Counter::increment() {
	counter++;
}

void Counter::reset() {
	counter = 0;
}

int Counter::get() const {
	return counter;
}

void Counter::draw() {
	std::string str_counter = std::to_string(counter);
	display.setColor(0);
	display.fillRect(0, 0, 48, 63);
	display.setColor(1);
	// TODO make a function for this
	int x = (48 - (str_counter.length() * 20)) / 2;
	x = std::max(0, x);
	display.printFixedN(x, 16, str_counter.c_str(), STYLE_NORMAL, 2);
}
