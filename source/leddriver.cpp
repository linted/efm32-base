#include "leddriver.h"
#include "i2cspm.h"
#include "i2cdriver.h"

#define KTD2061_ADDR 0xd0
#define KTD_ON 0xb8
#define KTD_OFF 0x38

constexpr uint8_t en_mode = 2;
constexpr uint8_t be_en = 1;
constexpr uint8_t ce_temp = 3;
constexpr uint8_t on = en_mode*64 + be_en*32 + ce_temp*8;
constexpr uint8_t off = be_en*32 + ce_temp*8;

LEDDriver::LEDDriver() :
    i2c::Device()
{
    // turn on the KTD
    write_reg(0x02, KTD_ON);
}

LEDDriver::~LEDDriver()
{
    write_reg(0x02, KTD_OFF);
}

void LEDDriver::set_led(uint32_t led_num, uint8_t r, uint8_t g, uint8_t b)
{
    if (led_num == 0x00){
        set_color0(r, g, b);
    } else if (led_num == 0x01) {
        set_color1(r, g, b);
    }
}

void LEDDriver::slow_off()
{
    write_reg(0x02, off+7);
}

void LEDDriver::global_reset()
{
    write_reg(0x02, 0xC0);
}

void LEDDriver::global_on(bool fade)
{
    write_reg(0x02, on + fade);
}

void LEDDriver::global_off(bool fade)
{
    write_reg(0x02, off + fade);
}

void LEDDriver::set_color0(uint8_t ired0, uint8_t igrn0, uint8_t iblu0)
{
    write_reg(0x05, iblu0);
    write_reg(0x04, igrn0);
    write_reg(0x03, ired0);
}

void LEDDriver::set_color1(uint8_t ired1, uint8_t igrn1, uint8_t iblu1)
{
    write_reg(0x08, iblu1);
    write_reg(0x07, igrn1);
    write_reg(0x06, ired1);
}

void LEDDriver::select_all(uint8_t isel)
{
    for (uint8_t reg = 0x09; reg < 0x0f; ++reg) {
        write_reg(reg, isel);
    }
}

void LEDDriver::select_off()
{
    select_all(0);
}

void LEDDriver::select_color0()
{
    select_all(0x88);
}

void LEDDriver::select_color1()
{
    select_all(0xff);
}

void LEDDriver::select_colors(uint8_t isela12, uint8_t isela34, uint8_t iselb12,
                              uint8_t iselb34, uint8_t iselc12, uint8_t iselc34)
{
    write_reg(0x09, isela12);
    write_reg(0x0A, isela34);
    write_reg(0x0B, iselb12);
    write_reg(0x0C, iselb34);
    write_reg(0x0D, iselc12);
    write_reg(0x0E, iselc34);
}

void LEDDriver::select_one(uint8_t reg, uint8_t data)
{
    write_reg(reg, data);
}

void LEDDriver::write_reg(uint8_t reg, uint8_t val)
{
    i2c::Sequence seq;

    seq.set_addr(KTD2061_ADDR);
    seq.output_buf() = { reg, val };
    seq.set_flags(I2C_FLAG_WRITE);

    transfer(seq);
}
