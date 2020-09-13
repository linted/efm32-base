#include "i2cdevice.h"
#include "i2cdriver.h"

namespace i2c {

Device::Device()
{

}

void Device::transfer(Sequence &seq)
{
    Driver::instance()->enqueue(seq);
}

} // namespace i2c
