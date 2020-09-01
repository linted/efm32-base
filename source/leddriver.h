#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "i2ccomponent.h"

#define LED_COUNT 12

class LEDDriver : public I2CComponent
{
public:
    LEDDriver();
    ~LEDDriver();

    void set_led(uint32_t led_num, uint8_t r, uint8_t g, uint8_t b);

private:
    void slow_off();
    void global_reset();
    void global_on(bool fade);
    void global_off(bool fade);
    void set_color0(uint8_t r, uint8_t g, uint8_t b);
    void set_color1(uint8_t r, uint8_t g, uint8_t b);
    void select_all(uint8_t isel);
    void select_off();
    void select_color0();
    void select_color1();
    void select_colors(uint8_t isela12, uint8_t isela34, uint8_t iselb12,
                       uint8_t iselb34, uint8_t iselc12, uint8_t iselc34);
    void select_one(uint8_t reg, uint8_t data);
    void select_one_clear(uint8_t reg, uint8_t data);

    void write_reg(uint8_t reg, uint8_t val);
};

#endif // LEDDRIVER_H
