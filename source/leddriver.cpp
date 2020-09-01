#include "leddriver.h"

LEDDriver::LEDDriver()
    : I2CComponent()
{

}

void LEDDriver::set_led(uint32_t led_num, bool val)
{
    if (led_num >= LED_COUNT) {
        return;
    }

    // construct an i2c message
}

void LEDDriver::toggle_led(uint32_t led_num)
{
    if (led_num >= LED_COUNT) {
        return;
    }

    set_led(led_num, !this->led_status[led_num]);
    this->led_status[led_num] = !this->led_status[led_num];
}
