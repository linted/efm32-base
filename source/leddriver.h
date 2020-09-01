#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "i2ccomponent.h"

#define LED_COUNT 12

class LEDDriver : public I2CComponent
{
public:
    LEDDriver();

    void set_led(uint32_t led_num, bool val);
    void toggle_led(uint32_t led_num);

private:
    bool led_status[LED_COUNT] = {false};
};

#endif // LEDDRIVER_H
