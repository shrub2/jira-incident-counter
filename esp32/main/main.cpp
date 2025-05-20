#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lcdgfx.h"

// Create a display instance (change model if needed)
DisplaySSD1306_128x64_I2C display(-1 /* reset pin */);

extern "C" void app_main(void)
{
    display.begin();
    display.clear();
    display.setFixedFont(ssd1306xled_font6x8);
    display.printFixed(0,  0, "Hello World!", STYLE_NORMAL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
