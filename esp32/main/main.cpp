#include <stdio.h>
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lcdgfx.h"
#include "Counter.h"

DisplaySSD1306_128x64_I2C display(-1);

void draw_ui() {
    display.setFixedFont(ssd1306xled_font5x7);
    display.printFixedN(57,  0, "days", STYLE_NORMAL, 1);
    display.printFixedN(57,  16, "without", STYLE_NORMAL, 1);
    display.printFixedN(57,  32, "docgen", STYLE_NORMAL, 1);
    display.printFixedN(57,  48, "issues", STYLE_NORMAL, 1);
}

extern "C" void app_main(void)
{
    Counter counter(0);

    display.begin();
    display.clear();
    draw_ui();
    while (1) {
    	counter.draw();
        vTaskDelay(pdMS_TO_TICKS(1000));
	counter.increment();
	if (counter.get() > 99) {
            counter.reset();
	};
    }
}
