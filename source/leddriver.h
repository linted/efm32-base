#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "i2ccomponent.h"

#define LED_COUNT 12

class LEDDriver : public I2CComponent
{
public:
    LEDDriver();

    void set_led(uint32_t led_num, uint8_t r, uint8_t g, uint8_t b);

private:
    void write_reg(uint8_t reg, uint8_t val);
};

#endif // LEDDRIVER_H
