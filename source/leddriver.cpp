#include "leddriver.h"
#include "i2cspm.h"

LEDDriver::LEDDriver()
    : I2CComponent()
{

}

void LEDDriver::set_led(uint32_t led_num, uint8_t r, uint8_t g, uint8_t b)
{
    I2C_TransferSeq_TypeDef seq;
    if (led_num >= LED_COUNT) {
        return;
    }

    // construct an i2c message


    send(&seq);
}
