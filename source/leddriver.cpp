#include "leddriver.h"
#include "i2cspm.h"

#define KTD2016_ADDR 104

struct I2C_LED_Message {
    uint8_t id;
    uint8_t monitor;
    uint8_t control;
    uint8_t IRED0;
    uint8_t IGRN0;
    uint8_t IBLU0;
    uint8_t IRED1;
    uint8_t IGRN1;
    uint8_t IBLU1;
    uint8_t ISELA12;
    uint8_t ISELA34;
    uint8_t ISELB12;
    uint8_t ISELB34;
    uint8_t ISELC12;
    uint8_t ISELC34;
} __attribute__((packed));

LEDDriver::LEDDriver()
    : I2CComponent()
{

}

void LEDDriver::set_led(uint32_t led_num, uint8_t r, uint8_t g, uint8_t b)
{
    I2C_TransferSeq_TypeDef seq;
    I2C_LED_Message msg;
    if (led_num >= LED_COUNT) {
        return;
    }

    // construct an i2c message
    seq.addr = KTD2016_ADDR;
    seq.flags = I2C_FLAG_WRITE;
    seq.buf->data = reinterpret_cast<uint8_t*>(&msg);
    seq.buf->len = sizeof(msg);



    send(&seq);
}
