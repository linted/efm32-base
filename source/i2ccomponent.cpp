#include "i2ccomponent.h"

bool I2CComponent::i2c_enabled = false;
I2CSPM_Init_TypeDef I2CComponent::i2c_init_val = I2CSPM_INIT_DEFAULT;

I2CComponent::I2CComponent()
{
    if (!i2c_enabled) {
        I2CSPM_Init(&i2c_init_val);
        i2c_enabled = true;
    }
}

void I2CComponent::send(I2C_TransferSeq_TypeDef *seq)
{
    I2CSPM_Transfer(I2C0, seq);
}
