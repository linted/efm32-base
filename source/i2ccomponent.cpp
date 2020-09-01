#include "i2ccomponent.h"

#include "em_chip.h"

bool I2CComponent::i2c_enabled = false;
I2CSPM_Init_TypeDef I2CComponent::i2c_init_val = I2CSPM_INIT_DEFAULT;

I2CComponent::I2CComponent()
{
    if (!i2c_enabled) {
        I2CSPM_Init(&i2c_init_val);
        i2c_enabled = true;
    }
}

I2C_TransferReturn_TypeDef I2CComponent::transfer(I2C_TransferSeq_TypeDef *seq)
{
    return I2CSPM_Transfer(I2C0, seq);
}
