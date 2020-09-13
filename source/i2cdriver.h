#ifndef I2CCOMPONENT_H
#define I2CCOMPONENT_H

#include <cstddef>
#include <list>

#include "bgmdevice.h"
#include "i2csequence.h"

namespace i2c {

class Driver : public BgmDevice
{
public:
    static Driver *instance();

    void trigger();
    virtual void process() override;
    virtual bool needs_processing() override;
    void enqueue(Sequence &seq);

private:
    Driver();

    std::list<Sequence> sequence_queue;
    bool triggered;

protected:

};

}

#endif // I2CCOMPONENT_H
