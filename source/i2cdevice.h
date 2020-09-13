#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include "i2csequence.h"

namespace i2c {

class Device
{
public:
    Device();

protected:
    void transfer(Sequence &seq);
};

} // namespace i2c

#endif // I2C_DEVICE_H
