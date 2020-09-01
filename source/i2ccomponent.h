#ifndef I2CCOMPONENT_H
#define I2CCOMPONENT_H

#include <stddef.h>
#include "i2cspm.h"


class I2CComponent
{
public:
    I2CComponent();

protected:
    void send(I2C_TransferSeq_TypeDef *seq);

private:
    static bool i2c_enabled;
    static I2CSPM_Init_TypeDef i2c_init_val;
};

#endif // I2CCOMPONENT_H
