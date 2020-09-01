#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "i2ccomponent.h"

class LEDDriver : public I2CComponent
{
public:
    LEDDriver();

    void set_led(uint32_t led_num, bool val);

};

#endif // LEDDRIVER_H
