#include "formula.hpp"
#include "randomnumgen.hpp"

Formula::Formula(uint64_t *loc) :
    loc(loc)
{

}

Formula::~Formula()
{

}

void Formula::mutate_with(Formula &other)
{
    RandomNumGen r;

    if((r.get_num() % 10) != 0)
    {
        return;
    }

    // first get the bits im missing that other has
    uint64_t missing = (~*this->loc) & *other.loc;

    // now activate bits on probablility
    uint64_t at = 1;
    while(at != 0)
    {
        if((r.get_num() % 10) == 0)
        {
            *this->loc &= (at & missing);
        }
        at <<= 1;
    }
}
