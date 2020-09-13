#ifndef I2C_SEQUENCE_H
#define I2C_SEQUENCE_H

#include <functional>
#include <em_i2c.h>
#include "types.h"

namespace i2c {

class Sequence
{
public:
    using CallBack = std::function<void(const Sequence&, void*)>;

    enum I2C_ADDR_TYPE {
        I2C_ADDR_7_BIT,
        I2C_ADDR_10_BIT,
    };

    Sequence();

    Bytes &intput_buf();
    Bytes &output_buf();
    void set_addr(uint16_t addr, I2C_ADDR_TYPE type = I2C_ADDR_7_BIT);
    void set_flags(uint16_t mask);
    void clear_flags(u_int16_t mask);
    void set_callback(const CallBack &cb);

    I2C_TransferSeq_TypeDef *build();

    static Sequence write(uint16_t addr, Bytes &data, I2C_ADDR_TYPE type = I2C_ADDR_7_BIT);

private:
    friend class Driver;

    enum {
        STATE_BUILDING,
        STATE_PENDING,
        STATE_TRANSFER,
    } transfer_state;

    Bytes _input_buf;
    Bytes _output_buf;
    I2C_TransferSeq_TypeDef _internal;
    CallBack _cb;
};

} // namespace i2c

#endif // I2C_SEQUENCE_H
