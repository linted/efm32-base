#include "leddriver.h"
#include "i2cspm.h"

LEDDriver::LEDDriver()
    : I2CComponent()
{

}

void LEDDriver::set_led(uint32_t led_num, bool val)
{
    I2C_TransferSeq_TypeDef seq;
    if (led_num >= LED_COUNT) {
        return;
    }

    // construct an i2c message


    send(&seq);
}

void LEDDriver::toggle_led(uint32_t led_num)
{
    if (led_num >= LED_COUNT) {
        return;
    }

    set_led(led_num, !this->led_status[led_num]);
    this->led_status[led_num] = !this->led_status[led_num];
}
