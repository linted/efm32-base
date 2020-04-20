#ifndef FORMULA_HPP
#define FORMULA_HPP

#include <cstdint>

class Formula
{
public:
    Formula(uint64_t *loc);
    ~Formula();

    void mutate_with(Formula &other);


private:
    volatile uint64_t *loc;
};


#endif
