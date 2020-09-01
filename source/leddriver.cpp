#include "leddriver.h"
#include "i2cspm.h"

#define KTD2016_ADDR 104

LEDDriver::LEDDriver()
    : I2CComponent()
{
    // turn on the KTD
    write_reg(0x02, 0xb8);
}

void LEDDriver::set_led(uint32_t led_num, uint8_t r, uint8_t g, uint8_t b)
{

}

void LEDDriver::write_reg(uint8_t reg, uint8_t val)
{
    uint8_t data[] = { reg, val };

    I2C_TransferSeq_TypeDef seq = {
      .addr = KTD2016_ADDR,
      .flags = I2C_FLAG_WRITE,
      .buf = {
        {
          .data = data,
          .len = 2
        },
        {0, 0}
      }
    };

    send(&seq);
}
