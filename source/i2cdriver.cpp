#include "i2cdriver.h"
#include "em_chip.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "em_cmu.h"

namespace i2c {

extern "C" {
void I2C0_IRQHandler(void)
{
    Driver::instance()->trigger();
}
}

static void init_i2c();

Driver *Driver::instance()
{
    static Driver d;

    return &d;
}

void Driver::trigger()
{
    triggered = true;
}

void Driver::process()
{
    if (!sequence_queue.empty()) {
        Sequence &curr = sequence_queue.front();
        I2C_TransferReturn_TypeDef t_ret;

        switch (curr.transfer_state) {
        case i2c::Sequence::STATE_BUILDING:
            // This is an error condition
            return;
        case i2c::Sequence::STATE_PENDING:
            t_ret = I2C_TransferInit(I2C0, curr.build());
            curr.transfer_state = i2c::Sequence::STATE_TRANSFER;
            break;
        case i2c::Sequence::STATE_TRANSFER:
            t_ret = I2C_Transfer(I2C0);
            break;
        }

        if (t_ret != i2cTransferInProgress) {
            sequence_queue.pop_front();
        }
    }

    triggered = false;
    I2C_IntClear(I2C0, ~0);
}

bool Driver::needs_processing()
{
    return triggered;
}

Driver::Driver()
{
    init_i2c();
}

void Driver::enqueue(Sequence &seq)
{
    Sequence s = seq;
    s.transfer_state = Sequence::STATE_PENDING;

    if (sequence_queue.empty()) {
        triggered = true;
    }

    sequence_queue.push_back(s);
}

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

}
