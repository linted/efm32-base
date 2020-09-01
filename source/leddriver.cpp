#include "leddriver.h"
#include "i2cspm.h"

#define KTD2016_ADDR 104
#define KTD_ON 0xb8
#define KTD_OFF 0x38

LEDDriver::LEDDriver()
    : I2CComponent()
{
    // turn on the KTD
    write_reg(0x02, KTD_ON);
}

void LEDDriver::set_led(uint32_t led_num, uint8_t r, uint8_t g, uint8_t b)
{
    write_reg(0x03, r);
    write_reg(0x04, g);
    write_reg(0x05, b);
    write_reg(0x09, 0xf0);
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
