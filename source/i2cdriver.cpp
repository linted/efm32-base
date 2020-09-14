#include "i2cdriver.h"
#include "em_chip.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "em_cmu.h"

#include "i2cspm.h"

namespace i2c {

// static void init_i2c();

Driver *Driver::instance()
{
    static Driver d;

    return &d;
}

Driver::Driver()
{
    init = I2CSPM_INIT_DEFAULT;
    I2CSPM_Init(&init);
}

void Driver::transfer(Sequence &seq)
{
    I2CSPM_Transfer(I2C0, seq.build());
}

#if 0
static void init_i2c()
{
    int i;
    I2C_Init_TypeDef i2cInit;

    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_I2C0, true);

    GPIO_PinModeSet(gpioPortB, 12, gpioModeWiredAndPullUp, 1);
    GPIO_PinModeSet(gpioPortB, 11, gpioModeWiredAndPullUp, 1);

    for (i = 0; i < 9; i++) {
        GPIO_PinOutSet(gpioPortB, 12);
        GPIO_PinOutSet(gpioPortB, 11);
    }

    I2C0->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
    I2C0->ROUTELOC0 = (6 << _I2C_ROUTELOC0_SDALOC_SHIFT)
            | (6 << _I2C_ROUTELOC0_SCLLOC_SHIFT);

    i2cInit.enable = true;
    i2cInit.master = true;
    i2cInit.freq = I2C_FREQ_STANDARD_MAX;
    i2cInit.refFreq = 0;
    i2cInit.clhr = i2cClockHLRStandard;

    I2C_Init(I2C0, &i2cInit);


}
#endif
}
