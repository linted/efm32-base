#include "i2csequence.h"
#include <cstring>

namespace i2c {

Sequence::Sequence()
{
    transfer_state = STATE_BUILDING;
    memset(&this->_internal, 0, sizeof(this->_internal));
}

Bytes &Sequence::intput_buf()
{
    return this->_input_buf;
}

Bytes &Sequence::output_buf()
{
    return this->_output_buf;
}

void Sequence::set_addr(uint16_t addr, Sequence::I2C_ADDR_TYPE type)
{
    if(type == I2C_ADDR_7_BIT)
    {
        this->_internal.addr = addr << 1;
    } else {
        // type == I2C_ADDR_10_BIT
        this->_internal.flags |= I2C_FLAG_10BIT_ADDR;
        this->_internal.addr = ((addr & 0x30) << 1) | (addr & 0x0f);
    }
}

void Sequence::set_flags(uint16_t mask)
{
    this->_internal.flags |= mask;
}

void Sequence::clear_flags(u_int16_t mask)
{
    this->_internal.flags &= ~mask;
}

I2C_TransferSeq_TypeDef *Sequence::build()
{
    this->_internal.buf[0].data = this->_output_buf.data();
    this->_internal.buf[0].len = this->_output_buf.length();
    this->_internal.buf[1].data = this->_input_buf.data();
    this->_internal.buf[1].len = this->_input_buf.length();

    return &this->_internal;
}

Sequence Sequence::write(uint16_t addr, Bytes &data, Sequence::I2C_ADDR_TYPE type)
{
    Sequence s;
    s.set_addr(addr, type);
    s.output_buf() = data;
    s.set_flags(I2C_FLAG_WRITE);

    return s;
}

} // namespace i2c
