#ifndef I2CCOMPONENT_H
#define I2CCOMPONENT_H

#include <cstddef>
#include <list>

#include "bgmdevice.h"
#include "i2csequence.h"
#include "i2cspm.h"

namespace i2c {

class Driver : public BgmDevice
{
public:
    static Driver *instance();

    void transfer(Sequence &seq);



private:
    Driver();

    I2CSPM_Init_TypeDef init;
};

}

#endif // I2CCOMPONENT_H
